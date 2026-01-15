#include <QTRSensors.h>

// ====================
// MOTOR PINLERİ
// ====================
// Her motor için 2 pin kullanıyoruz
#define AIN1 5   // Sol motor
#define AIN2 6
#define BIN1 9   // Sağ motor
#define BIN2 10

// ====================
// QTR SENSÖRLER
// ====================
QTRSensors qtr;

const uint8_t sensorCount = 8;
uint16_t sensorValues[sensorCount];

// ====================
// AYARLAR
// ====================
int hiz = 180;      // Robotun normal hızı
int donus = 150;   // Dönüş hızı
int ref = 500;     // Siyah çizgi algılama sınırı

void setup()
{
  Serial.begin(9600);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  // Sensör ayarları
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0,A1,A2,A3,A4,A5,A6,A7}, sensorCount);
  qtr.setEmitterPin(2);

  delay(500);

  // ===== KALİBRASYON =====
  // Robotu çizgi üstünde sağa sola gezdiriyoruz
  for (int i = 0; i < 100; i++)
  {
    qtr.calibrate();
    delay(20);
  }
}

void loop()
{
  // Sensörleri oku
  qtr.read(sensorValues);

  // Orta sensörler çizgiyi görüyor mu?
  bool orta = sensorValues[3] > ref || sensorValues[4] > ref;

  // Sol taraf çizgiyi görüyor mu?
  bool sol  = sensorValues[0] > ref || sensorValues[1] > ref || sensorValues[2] > ref;

  // Sağ taraf çizgiyi görüyor mu?
  bool sag  = sensorValues[5] > ref || sensorValues[6] > ref || sensorValues[7] > ref;

  // =====================
  // ÇİZGİ TAKİP KARARI
  // =====================

  // 1) ORTA ÇİZGİYİ GÖRÜRSE → DÜZ GİT
  if (orta && !sol && !sag)
  {
    analogWrite(AIN1, hiz);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, hiz);
    analogWrite(BIN2, 0);
  }

  // 2) ÇİZGİ SOLDA → SOLA DÖN
  else if (sol && !orta)
  {
    analogWrite(AIN1, 80);      // Sol motor yavaş
    analogWrite(AIN2, 0);
    analogWrite(BIN1, donus);   // Sağ motor hızlı
    analogWrite(BIN2, 0);
  }

  // 3) ÇİZGİ SAĞDA → SAĞA DÖN
  else if (sag && !orta)
  {
    analogWrite(AIN1, donus);   // Sol motor hızlı
    analogWrite(AIN2, 0);
    analogWrite(BIN1, 80);      // Sağ motor yavaş
    analogWrite(BIN2, 0);
  }

  // 4) ORTA + SOL → HAFİF SOLA
  else if (orta && sol)
  {
    analogWrite(AIN1, hiz - 60);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, hiz);
    analogWrite(BIN2, 0);
  }

  // 5) ORTA + SAĞ → HAFİF SAĞA
  else if (orta && sag)
  {
    analogWrite(AIN1, hiz);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, hiz - 60);
    analogWrite(BIN2, 0);
  }

  // 6) HİÇBİRİ GÖRMÜYOR → DUR
  else
  {
    analogWrite(AIN1, 0);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, 0);
    analogWrite(BIN2, 0);
  }

  delay(5);
}
