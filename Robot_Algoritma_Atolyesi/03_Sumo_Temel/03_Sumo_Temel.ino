#include <Arduino.h>
// Emre Demiroz - Mucit Akademisi. Robot verilen pin duzenine gore.
const uint8_t L1=5,L2=6,R1=9,R2=10,START=7,TACTIC=2;
const uint8_t LED1=11,LED2=12,LED3=13,BUZZER=3;
bool armed=false, lastButton=false;
uint32_t buttonChanged=0;
bool rawButton=false;
int limitPWM(int v){return constrain(v,-180,180);}
void motor(int left,int right){
  left=limitPWM(left); right=limitPWM(right);
  // Once iki yonu kapat: yon degisiminde eski PWM acik kalmasin.
  analogWrite(L1,0); analogWrite(L2,0); analogWrite(R1,0); analogWrite(R2,0);
  analogWrite(left>=0?L1:L2,abs(left));
  analogWrite(right>=0?R1:R2,abs(right));
}
void hardware(){
  const uint8_t pins[]={L1,L2,R1,R2,LED1,LED2,LED3,BUZZER};
  for(uint8_t p:pins)pinMode(p,OUTPUT);
  pinMode(START,INPUT_PULLUP);pinMode(TACTIC,INPUT_PULLUP);
  Serial.begin(115200);motor(0,0);
}
bool startPressed(){
  uint32_t now=millis(); bool b=digitalRead(START)==LOW;
  if(b!=rawButton){rawButton=b;buttonChanged=now;}
  if((uint32_t)(now-buttonChanged)<30)return false;
  bool edge=b&&!lastButton;lastButton=b;return edge;
}
struct PID {
  float integral=0,prev=0,deriv=0; bool fresh=true;
  void reset(){integral=prev=deriv=0;fresh=true;}
  float step(float error,float dt,float kp,float ki,float kd,float cap){
    if(dt<=0 || dt>0.1f){reset();dt=0.01f;}
    float d=fresh?0:(error-prev)/dt;
    deriv=0.7f*deriv+0.3f*d;fresh=false;prev=error;
    float candidate=constrain(integral+error*dt,-1.0f,1.0f);
    float u=kp*error+ki*candidate+kd*deriv;
    if(abs(u)<cap || u*error<0)integral=candidate;
    return constrain(kp*error+ki*integral+kd*deriv,-cap,cap);
  }
};


// D11=1, D12=2, D13=4. D2 LOW=sol, HIGH=sag.
uint8_t tactic=0;
void showTactic(){
 digitalWrite(LED1,(tactic & 1)!=0);
 digitalWrite(LED2,(tactic & 2)!=0);
 digitalWrite(LED3,(tactic & 4)!=0);
}

const uint8_t REMOTE_PIN=4; // VARSAYIM: kart uzerinde dogrula.
// Yalniz cozulmus, surekli HIGH=git / LOW=dur cikisli MODUL icin.
// Ham IR alicisinin darbelerini bu kodla baslatma komutu saymayin!
const bool REMOTE_READY=false; // D4 testi tamamlaninca true.
bool remoteLowSeen=false;
uint32_t highSince=0;bool wasHigh=false;
bool remoteGo(){
 bool high=digitalRead(REMOTE_PIN)==HIGH;
 if(!high){remoteLowSeen=true;wasHigh=false;return false;}
 if(!wasHigh){wasHigh=true;highSince=millis();}
 return REMOTE_READY && remoteLowSeen && millis()-highSince>=100;
}
void remoteSetup(){pinMode(REMOTE_PIN,INPUT);}

// MIDI SUMO: sadece A0/A1 Sharp, kenar sensoru YOK.
const bool USE_PID=false;

const bool SENSOR_READY=false; // Kalibrasyonu tamamla, sonra true yap.
const int NEAR_L=400,NEAR_R=400;
const int RAW_FAR_L=100,RAW_NEAR_L=700,RAW_FAR_R=100,RAW_NEAR_R=700;
// 8 egitim taktigi: ilk dordunde sabit arama, son dordunde yon degisimi.
const int ATTACK[8]={65,75,85,95,65,75,85,95};
const int SEARCH[8]={35,40,45,50,35,40,45,50};
uint32_t lastTick=0,seenAt=0,runAt=0;
bool running=false,timedOut=false,runRight=true;
uint8_t runTactic=0;PID pid;
float strength(int v,int farV,int nearV){
 if(nearV<=farV)return 0;
 return constrain(float(v-farV)/(nearV-farV),0.0f,1.0f);
}
void setup(){hardware();remoteSetup();showTactic();}
void loop(){
 uint32_t now=millis();bool pressed=startPressed();
 bool go=remoteGo();
 if(!go || !SENSOR_READY){
  motor(0,0);pid.reset();running=false;
  if(digitalRead(REMOTE_PIN)==LOW){
   timedOut=false;
   if(pressed){tactic=(tactic+1)%8;showTactic();}
  }
  return;
 }
 if(timedOut){motor(0,0);return;}
 if(!running){
  running=true;runTactic=tactic;runRight=digitalRead(TACTIC)==HIGH;
  seenAt=runAt=now;lastTick=now;pid.reset();
 }
 if(now-lastTick<50)return;
 float dt=(now-lastTick)/1000.0f;lastTick=now;
 int l=analogRead(A0),r=analogRead(A1);
 bool left=l>=NEAR_L,right=r>=NEAR_R;
 if(!left&&!right){
  pid.reset();
  if(now-seenAt>=15000){timedOut=true;motor(0,0);return;}
  bool clockwise=runRight;
  if(runTactic>=4 && ((now-runAt)/1500)%2)clockwise=!clockwise;
  int speed=SEARCH[runTactic];motor(clockwise?speed:-speed,clockwise?-speed:speed);
  return;
 }
 seenAt=now;int forward=ATTACK[runTactic];
 if(!USE_PID){
  if(left&&right)motor(forward,forward);
  else if(right)motor(60,-60);else motor(-60,60);
  return;
 }
 float ls=strength(l,RAW_FAR_L,RAW_NEAR_L),rs=strength(r,RAW_FAR_R,RAW_NEAR_R);
 float error=(rs-ls)/(rs+ls+0.01f);
 // P simdiki farki, I biriken farki, D degisim hizini kullanir.
 float correction=pid.step(error,dt,60.0f,0.0f,0.3f,70.0f);
 if(!(left&&right))forward=50;
 motor(forward+(int)correction,forward-(int)correction);
}
