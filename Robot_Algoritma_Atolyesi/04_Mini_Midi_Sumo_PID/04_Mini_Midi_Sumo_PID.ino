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

// Mini / midi: fiziksel sinif degil, dusuk hizli deney profili secimi.
const bool MIDI_PROFILE=false;
const bool USE_PID=true;
const bool SENSOR_READY=false; // Kalibrasyon tamamlaninca true yap.
const int NEAR_L=400,NEAR_R=400;const bool NEAR_IS_HIGH=true;
// A2 sol on, A3 sag on ring kenari. Acik zemin yuksek varsayimi.
const bool EDGE_IS_HIGH=true;const int EDGE_L=700,EDGE_R=700;
const int RAW_FAR_L=100,RAW_NEAR_L=700,RAW_FAR_R=100,RAW_NEAR_R=700;
const int attackSpeed=MIDI_PROFILE?100:90,searchSpeed=45;
uint32_t readyAt=0,phaseAt=0,lastTick=0,seenAt=0;
enum Phase{IDLE,WAIT,SEEK,RETREAT,TURN};Phase phase=IDLE;
bool turnRight=true;PID pid;
bool active(int v,int t,bool high){return high?v>=t:v<=t;}
float strength(int value,int farValue,int nearValue){
 if(nearValue==farValue)return 0;
 return constrain((float)(value-farValue)/(nearValue-farValue),0.0f,1.0f);
}
void setup(){hardware();}
void loop(){
 uint32_t now=millis();
 if(startPressed()){
  if(phase==IDLE && SENSOR_READY){phase=WAIT;readyAt=now;}
  else phase=IDLE;
  motor(0,0);pid.reset();
 }
 if(phase==IDLE){motor(0,0);return;}
 if(phase==WAIT){motor(0,0);if(now-readyAt>=5000){phase=SEEK;seenAt=now;}return;}
 // Ring kenari, rakip ve PID'den her zaman onceliklidir.
 bool edgeL=active(analogRead(A2),EDGE_L,EDGE_IS_HIGH);
 bool edgeR=active(analogRead(A3),EDGE_R,EDGE_IS_HIGH);
 if((edgeL||edgeR) && phase!=RETREAT){
  turnRight=edgeL&&!edgeR?true:edgeR&&!edgeL?false:digitalRead(TACTIC)==HIGH;
  phase=RETREAT;phaseAt=now;pid.reset();
 }
 if(phase==RETREAT){motor(-90,-90);if(now-phaseAt>=220){phase=TURN;phaseAt=now;}return;}
 if(phase==TURN){motor(turnRight?65:-65,turnRight?-65:65);if(now-phaseAt>=180)phase=SEEK;return;}
 if(now-lastTick<10)return;
 float dt=(now-lastTick)/1000.0f;lastTick=now;
 int l=analogRead(A0),r=analogRead(A1);
 bool left=active(l,NEAR_L,NEAR_IS_HIGH),right=active(r,NEAR_R,NEAR_IS_HIGH);
 if(!left&&!right){
  pid.reset();
  // En fazla 15 sn arama; kor deneme surusu devam etmesin.
  if(now-seenAt>15000){phase=IDLE;motor(0,0);return;}
  bool clockwise=digitalRead(TACTIC)==HIGH;
  motor(clockwise?searchSpeed:-searchSpeed,clockwise?-searchSpeed:searchSpeed);return;
 }
 seenAt=now;
 if(!USE_PID){
  if(left&&right)motor(attackSpeed,attackSpeed);
  else if(right)motor(70,-70);else motor(-70,70);
  return;
 }
 float ls=strength(l,RAW_FAR_L,RAW_NEAR_L),rs=strength(r,RAW_FAR_R,RAW_NEAR_R);
 // Pozitif hata: rakip sagda; sol motor hizlanir.
 float error=(rs-ls)/(rs+ls+0.01f);
 float u=pid.step(error,dt,90.0f,0.0f,0.8f,100.0f);
 int forward=left&&right?attackSpeed:60;
 motor(forward+(int)u,forward-(int)u);
}
