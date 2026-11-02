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


const uint8_t REMOTE_PIN=4; // Varsayilan, kabloyu dogrula.
bool previous=false;uint32_t changedAt=0,lastPrint=0,beepAt=0;bool sounded=false;
void setup(){hardware();pinMode(REMOTE_PIN,INPUT);}
void loop(){
 motor(0,0); // IR testi asla motor surmez.
 uint32_t now=millis();bool high=digitalRead(REMOTE_PIN)==HIGH;
 if(high!=previous){previous=high;changedAt=now;sounded=false;}
 digitalWrite(LED1,high);digitalWrite(LED2,LOW);digitalWrite(LED3,LOW);
 if(high && !sounded && now-changedAt>=100){tone(BUZZER,1600);beepAt=now;sounded=true;}
 if(!high || (sounded && now-beepAt>=150))noTone(BUZZER);
 if(now-lastPrint>=100){lastPrint=now;Serial.print("D4=");Serial.println(high?1:0);}
}
