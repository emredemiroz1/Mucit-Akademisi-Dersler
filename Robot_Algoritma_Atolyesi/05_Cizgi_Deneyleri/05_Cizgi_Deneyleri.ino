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

enum Mode{SINGLE_CENTER,SINGLE_EDGE,TWO_BOUNDARIES};
const Mode MODE=SINGLE_CENTER; // Iki cizgi arasi icin TWO_BOUNDARIES.
const bool BLACK_HIGH=true;const int THRESHOLD=500;
const uint8_t S[]={A0,A1,A2,A3,A4,A5,A6,A7}; // Soldan saga!
int lowRaw[8],highRaw[8]; bool validCalibration=false;uint32_t calibrationAt;
bool calibrating=true;PID pid;uint32_t lastTick=0,lostAt=0;
void setup(){hardware();calibrationAt=millis();for(int i=0;i<8;i++){lowRaw[i]=1023;highRaw[i]=0;}}
void loop(){
 uint32_t now=millis();
 if(calibrating){
  motor(0,0); // Robotu ELLE gezdir; her sensor siyah ve beyazi gorsun.
  for(int i=0;i<8;i++){int v=analogRead(S[i]);lowRaw[i]=min(lowRaw[i],v);highRaw[i]=max(highRaw[i],v);}
  if(now-calibrationAt>=5000){calibrating=false;validCalibration=true;
   for(int i=0;i<8;i++)if(highRaw[i]-lowRaw[i]<100)validCalibration=false;
   Serial.println(validCalibration?"Kalibrasyon hazir":"Kalibrasyon gecersiz: resetle ve elle gezdir");
  }return;
 }
 if(startPressed()&&validCalibration){armed=!armed;pid.reset();lostAt=0;}
 if(!armed){motor(0,0);return;}
 if(now-lastTick<10)return;
 float dt=(now-lastTick)/1000.0f;lastTick=now;
 float value[8];int starts[4],ends[4],groups=0;bool in=false;
 for(int i=0;i<8;i++){
  value[i]=constrain((analogRead(S[i])-lowRaw[i])*1000L/(highRaw[i]-lowRaw[i]),0L,1000L);
  if(!BLACK_HIGH)value[i]=1000-value[i];
  bool on=value[i]>=THRESHOLD;
  if(on&&!in){starts[groups]=i;ends[groups]=i;groups++;}
  if(on)ends[groups-1]=i;
  in=on;
 }
 bool found=false;float position=3500;
 if(MODE==TWO_BOUNDARIES){
  // Iki AYRI sensor grubu gorulmeli; tek cizgi gorunce ortalama uydurma.
  if(groups==2 && ends[0]<starts[1]){
   position=(ends[0]+starts[1])*500.0f;found=true;
  }
 }else if(groups==1 && ends[0]-starts[0]<6){
  if(MODE==SINGLE_CENTER){float sum=0,weighted=0;
   for(int i=starts[0];i<=ends[0];i++){sum+=value[i];weighted+=value[i]*i*1000.0f;}
   position=weighted/sum;found=true;
  }else{position=ends[0]*1000.0f+500;found=true;} // Siyah grubun sag kenari.
 }
 if(!found){
  motor(0,0);pid.reset();if(lostAt==0)lostAt=now;
  if(now-lostAt>=300)armed=false;
  return;
 }
 lostAt=0;float error=(position-3500)/3500.0f;
 float u=pid.step(error,dt,100,0,1.2f,90);
 int speed=80-(int)(35*abs(error));motor(speed+(int)u,speed-(int)u);
}
