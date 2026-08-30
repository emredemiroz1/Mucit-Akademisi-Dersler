/*
========================================================
ÇİZGİ İZLEYEN ROBOTUN MANTIĞI (ÖĞRENCİLER İÇİN)
========================================================
1) Robotun altında 8 tane çizgi sensörü var. Bu sensörler siyah çizgiyi görünce değerleri yükselir.
2) Robot her an sensörlere bakar ve çizginin nerede olduğunu hesaplar (sol mu, orta mı, sağ mı?).
3) Çizgi ortadaysa robot dümdüz gider. Çizgi sağa kaydıysa robot sağa yaklaşır, sola kaydıysa sola yaklaşır.
4) PID denen yöntem robotun “ne kadar döneceğini” hesaplar:
   - Kp: Hata varsa hemen düzeltmeye çalışır.
   - Ki: Uzun süre aynı tarafa kayarsa bunu telafi eder.
   - Kd: Çok hızlı sapmalarda aşırı dönmeyi engeller.
5) Bazı özel durumlar var:
   - Tüm sensörler siyah görürse (kavşak/işaret): sayaç artar, 1. sefer sola, 2. sefer yumuşak sağ yapılır.
   - Sol taraf sensörler siyahsa veya sağ taraf sensörler siyahsa 90 derece dönüş yapılır.
   - Hiç sensör siyah görmüyorsa çizgi kaybolmuş olabilir: integral ve hata sıfırlanır.
========================================================
*/

#include <QTRSensors.h>   // QTR çizgi sensörü kütüphanesi

// ======================================================
// MOTOR SÜRÜCÜ (TB6612) BAĞLANTILARI (PWM ile hız kontrolü)
// ======================================================
#define AIN1 5   // Sol motor kontrol 1 (PWM)
#define AIN2 6   // Sol motor kontrol 2 (PWM)
#define BIN1 9   // Sağ motor kontrol 1 (PWM)
#define BIN2 10  // Sağ motor kontrol 2 (PWM)

// ======================================================
// QTR-8A SENSÖR AYARLARI
// ======================================================
QTRSensors qtr;

const uint8_t sensorCount = 8;          // 8 sensör var
uint16_t sensorValues[sensorCount];     // sensör değerleri burada tutulur

// ======================================================
// PID AYARLARI
// ======================================================
float Kp = 0.04;     // Hata olunca ne kadar düzeltme yapılacak?
float Ki = 0.0001;   // Uzun süreli kaymaları düzeltmeye yardım eder
float Kd = 0.5;      // Ani sapmalarda dengeler

float lastError = 0;   // Bir önceki hata
float integral  = 0;   // Hataların toplamı

int baseSpeed = 200;   // Robotun düz giderken hızı (0-255)
int turnSpeed = 100;   // Sert dönüşlerde kullanılacak hız

int sayac = 0;         // Kavşak/işaret sayacı
int ref = 500;         // “Siyah gördü” demek için eşik değer

// ======================================================
// SETUP: Robot açılınca 1 kere çalışır
// ======================================================
void setup()
{
  Serial.begin(9600);

  // Motor pinleri çıkış olur
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  // QTR sensör ayarları
  qtr.setTypeAnalog(); // analog sensör okuma
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, sensorCount);
  qtr.setEmitterPin(2); // sensör LED pini (gerekirse)

  delay(500);

  // ======================================================
  // SENSÖR KALİBRASYONU
  // Sensörler siyah ve beyazı öğrenir.
  // ======================================================
  Serial.println("Sensör Kalibrasyonu Başlıyor...");

  for (int i = 0; i < 100; i++)
  {
    qtr.calibrate();
    delay(20);
  }

  Serial.println("Kalibrasyon Tamamlandı!");
}

// ======================================================
// LOOP: Sürekli tekrar eder
// ======================================================
void loop()
{
  // Çizginin konumu bulunur (0 - 7000 arası düşün)
  int position = qtr.readLineBlack(sensorValues);

  // 3500 robotun “orta” kabul ettiği noktadır
  int error = position - 3500;

  // ======================================================
  // 1) TÜM SENSÖRLER SİYAHSA (kavşak/işaret gibi)
  // ======================================================
  if (sensorValues[7] > ref && sensorValues[6] > ref && sensorValues[5] > ref && sensorValues[4] > ref &&
      sensorValues[3] > ref && sensorValues[2] > ref && sensorValues[1] > ref && sensorValues[0] > ref)
  {
    sayac++;      // işaret say
    delay(10);

    // 1. işaret: sola dön
    if (sayac == 1)
    {
      turnLeft();
      delay(100);

      // Çizgiyi tekrar bulana kadar bekle
      do {
        qtr.read(sensorValues);
      } while (sensorValues[4] > ref);

      return;
    }

    // 2. işaret: yumuşak sağ yap
    if (sayac == 2)
    {
      softRight();
      delay(100);

      // Çizgiyi tekrar bulana kadar bekle
      do {
        qtr.read(sensorValues);
      } while (sensorValues[3] > ref);

      sayac = 0; // iki işaret tamam, sayaç sıfırla
      return;
    }

    return;
  }

  // ======================================================
  // 2) 90 DERECE DÖNÜŞ DURUMLARI
  // ======================================================

  // Sol taraftaki 4 sensör siyahsa: keskin dönüş (kod sağa dönüyor)
  if (sensorValues[0] > ref && sensorValues[1] > ref && sensorValues[2] > ref && sensorValues[3] > ref)
  {
    turnRight();
    delay(80);

    // Çizgiyi tekrar yakalayana kadar bekle
    do {
      qtr.read(sensorValues);
    } while (sensorValues[4] < ref);

    return;
  }

  // Sağ taraftaki 4 sensör siyahsa: keskin dönüş (kod sola dönüyor)
  if (sensorValues[7] > ref && sensorValues[6] > ref && sensorValues[5] > ref && sensorValues[4] > ref)
  {
    turnLeft();
    delay(80);

    // Çizgiyi tekrar yakalayana kadar bekle
    do {
      qtr.read(sensorValues);
    } while (sensorValues[3] < ref);

    return;
  }

  // ======================================================
  // 3) HİÇBİR SENSÖR SİYAH DEĞİLSE (çizgi kaybolmuş olabilir)
  // ======================================================
  if (sensorValues[7] < 800 && sensorValues[6] < 800 && sensorValues[5] < 800 && sensorValues[4] < 800 &&
      sensorValues[3] < 800 && sensorValues[2] < 800 && sensorValues[1] < 800 && sensorValues[0] < 800)
  {
    // PID’nin birikmiş hatalarını sıfırla
    integral = 0;
    lastError = 0;

    // İstenirse burada durdurulabilir:
    // setMotorSpeed(0, 0);
    // delay(100);

    return;
  }

  // ======================================================
  // 4) PID HESABI (çizgiyi takip için düzeltme)
  // ======================================================
  integral += error;                    // hata birikir
  float derivative = error - lastError; // hata ne kadar değişti?
  float correction = (Kp * error) + (Ki * integral) + (Kd * derivative);

  lastError = error;

  // Düzeltmeye göre hızları ayarla
  int leftSpeed  = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  // Hızları 0-255 aralığında tut
  leftSpeed  = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // Motorları çalıştır
  setMotorSpeed(leftSpeed, rightSpeed);
}

// ======================================================
// MOTOR HIZ AYAR FONKSİYONU
// Burada iki motorun hızını PWM ile ayarlar.
// ======================================================
void setMotorSpeed(int leftSpeed, int rightSpeed)
{
  // Sol motor (kodun orijinalindeki gibi)
  analogWrite(AIN1, rightSpeed);
  analogWrite(AIN2, 0);

  // Sağ motor (kodun orijinalindeki gibi)
  analogWrite(BIN1, leftSpeed);
  analogWrite(BIN2, 0);
}

// ======================================================
// SERT SOL DÖNÜŞ
// ======================================================
void turnLeft()
{
  analogWrite(AIN1, 0);
  analogWrite(AIN2, turnSpeed);

  analogWrite(BIN1, turnSpeed);
  analogWrite(BIN2, 0);
}

// ======================================================
// SERT SAĞ DÖNÜŞ
// ======================================================
void turnRight()
{
  analogWrite(AIN1, turnSpeed);
  analogWrite(AIN2, 0);

  analogWrite(BIN1, 0);
  analogWrite(BIN2, turnSpeed);
}

// ======================================================
// YUMUŞAK SAĞ DÖNÜŞ
// ======================================================
void softRight()
{
  // önce kısa bir sağ dönüş
  analogWrite(AIN1, turnSpeed);
  analogWrite(AIN2, 0);

  analogWrite(BIN1, 0);
  analogWrite(BIN2, turnSpeed);

  delay(150);

  // sonra daha yumuşak dönsün diye bir motoru yavaşlat
  analogWrite(AIN1, turnSpeed);
  analogWrite(AIN2, 0);

  analogWrite(BIN1, 50);
  analogWrite(BIN2, 0);
}

// ======================================================
// YUMUŞAK SOL DÖNÜŞ (kodda kullanılmıyor ama hazır)
// ======================================================
void softLeft()
{
  analogWrite(AIN1, 50);
  analogWrite(AIN2, 0);

  analogWrite(BIN1, turnSpeed);
  analogWrite(BIN2, 0);
}

// ======================================================
// DUR / BEKLE
// ======================================================
void wait()
{
  analogWrite(AIN1, 0);
  analogWrite(AIN2, 0);

  analogWrite(BIN1, 0);
  analogWrite(BIN2, 0);
}
