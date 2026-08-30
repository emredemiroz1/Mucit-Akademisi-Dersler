// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Profesyonel Cizgi Izleyen - Fansiz PID'siz Taslak
// ROBOMER kart pinleri:
// Sag motor: D5-D6, Sol motor: D9-D10
// Cizgi sensorleri: A0-A7

#include <QTRSensors.h>

int sagMotor1 = 5;
int sagMotor2 = 6;
int solMotor1 = 9;
int solMotor2 = 10;

int normalHiz = 150;
int donusHizi = 120;
int siyahEsik = 500;

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

  // Kalibrasyon icin robotu siyah ve beyaz zemin uzerinde gezdirin.
  for (int i = 0; i < 100; i++) {
    qtr.calibrate();
    delay(20);
  }
}

void loop() {
  qtr.read(sensorDegerleri);

  bool solCizgi = sensorDegerleri[0] > siyahEsik || sensorDegerleri[1] > siyahEsik || sensorDegerleri[2] > siyahEsik;
  bool ortaCizgi = sensorDegerleri[3] > siyahEsik || sensorDegerleri[4] > siyahEsik;
  bool sagCizgi = sensorDegerleri[5] > siyahEsik || sensorDegerleri[6] > siyahEsik || sensorDegerleri[7] > siyahEsik;

  if (ortaCizgi && !solCizgi && !sagCizgi) {
    ileri(normalHiz);
  } else if (solCizgi && !ortaCizgi) {
    solaDuzelt();
  } else if (sagCizgi && !ortaCizgi) {
    sagaDuzelt();
  } else if (ortaCizgi && solCizgi) {
    solaHafifDuzelt();
  } else if (ortaCizgi && sagCizgi) {
    sagaHafifDuzelt();
  } else {
    dur();
  }

  delay(5);
}

void ileri(int hiz) {
  analogWrite(sagMotor1, hiz);
  digitalWrite(sagMotor2, LOW);
  analogWrite(solMotor1, hiz);
  digitalWrite(solMotor2, LOW);
}

void solaDuzelt() {
  analogWrite(sagMotor1, donusHizi);
  digitalWrite(sagMotor2, LOW);
  analogWrite(solMotor1, 60);
  digitalWrite(solMotor2, LOW);
}

void sagaDuzelt() {
  analogWrite(sagMotor1, 60);
  digitalWrite(sagMotor2, LOW);
  analogWrite(solMotor1, donusHizi);
  digitalWrite(solMotor2, LOW);
}

void solaHafifDuzelt() {
  analogWrite(sagMotor1, normalHiz);
  digitalWrite(sagMotor2, LOW);
  analogWrite(solMotor1, normalHiz - 50);
  digitalWrite(solMotor2, LOW);
}

void sagaHafifDuzelt() {
  analogWrite(sagMotor1, normalHiz - 50);
  digitalWrite(sagMotor2, LOW);
  analogWrite(solMotor1, normalHiz);
  digitalWrite(solMotor2, LOW);
}

void dur() {
  digitalWrite(sagMotor1, LOW);
  digitalWrite(sagMotor2, LOW);
  digitalWrite(solMotor1, LOW);
  digitalWrite(solMotor2, LOW);
}
