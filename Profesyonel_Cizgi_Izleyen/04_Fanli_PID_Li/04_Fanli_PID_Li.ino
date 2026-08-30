// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Profesyonel Cizgi Izleyen - Fanli PID'li Taslak
// ROBOMER kart pinleri:
// Sag motor: D5-D6, Sol motor: D9-D10
// Cizgi sensorleri: A0-A7
// Fan cikisi: D2

#include <QTRSensors.h>

int sagMotor1 = 5;
int sagMotor2 = 6;
int solMotor1 = 9;
int solMotor2 = 10;
int fan2 = 2;

int temelHiz = 190;
int enYuksekHiz = 255;
int fanHizi = 200;

float Kp = 0.055;
float Ki = 0.0001;
float Kd = 0.75;

int sonHata = 0;
float toplamHata = 0;

QTRSensors qtr;
const uint8_t sensorSayisi = 8;
uint16_t sensorDegerleri[sensorSayisi];

void setup() {
  Serial.begin(9600);

  pinMode(sagMotor1, OUTPUT);
  pinMode(sagMotor2, OUTPUT);
  pinMode(solMotor1, OUTPUT);
  pinMode(solMotor2, OUTPUT);
  pinMode(fan2, OUTPUT);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, sensorSayisi);

  for (int i = 0; i < 120; i++) {
    qtr.calibrate();
    delay(20);
  }

  analogWrite(fan2, fanHizi);
}

void loop() {
  int konum = qtr.readLineBlack(sensorDegerleri);
  int hata = konum - 3500;

  toplamHata = toplamHata + hata;
  toplamHata = constrain(toplamHata, -10000, 10000);

  int hataDegisimi = hata - sonHata;
  int duzeltme = (Kp * hata) + (Ki * toplamHata) + (Kd * hataDegisimi);

  sonHata = hata;

  int sagHiz = temelHiz - duzeltme;
  int solHiz = temelHiz + duzeltme;

  sagHiz = constrain(sagHiz, 0, enYuksekHiz);
  solHiz = constrain(solHiz, 0, enYuksekHiz);

  motorlariSur(sagHiz, solHiz);
}

void motorlariSur(int sagHiz, int solHiz) {
  analogWrite(sagMotor1, sagHiz);
  digitalWrite(sagMotor2, LOW);

  analogWrite(solMotor1, solHiz);
  digitalWrite(solMotor2, LOW);
}

void dur() {
  digitalWrite(sagMotor1, LOW);
  digitalWrite(sagMotor2, LOW);
  digitalWrite(solMotor1, LOW);
  digitalWrite(solMotor2, LOW);
}
