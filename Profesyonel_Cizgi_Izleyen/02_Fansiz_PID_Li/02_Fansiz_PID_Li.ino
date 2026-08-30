// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Profesyonel Cizgi Izleyen - Fansiz PID'li Taslak
// ROBOMER kart pinleri:
// Sag motor: D5-D6, Sol motor: D9-D10
// Cizgi sensorleri: A0-A7

#include <QTRSensors.h>

int sagMotor1 = 5;
int sagMotor2 = 6;
int solMotor1 = 9;
int solMotor2 = 10;

int temelHiz = 170;
int enYuksekHiz = 230;

float Kp = 0.05;
float Ki = 0.0001;
float Kd = 0.6;

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

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, sensorSayisi);

  for (int i = 0; i < 120; i++) {
    qtr.calibrate();
    delay(20);
  }
}

void loop() {
  int konum = qtr.readLineBlack(sensorDegerleri);

  // QTR 8 sensor icin orta nokta yaklasik 3500'dur.
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
