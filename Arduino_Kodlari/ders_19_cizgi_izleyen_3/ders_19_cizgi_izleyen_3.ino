#include <QTRSensors.h>

// Motor sürücü TB6612 bağlantıları
#define AIN1 6   // Sol motor PWM
#define AIN2 5   // Sol motor PWM
#define BIN1 9   // Sağ motor PWM
#define BIN2 10  // Sağ motor PWM

// QTR-8A Sensör nesnesi
QTRSensors qtr;
const uint8_t sensorCount = 8;
uint16_t sensorValues[sensorCount];

// PID Değişkenleri
float Kp = 0.09;    // Oransal kazanç
float Ki = 0.00001;  // İntegral kazanç
float Kd = 0.5;     // Türevsel kazanç
float lastError = 0, integral = 0;

int baseSpeed = 125;  // Sabit hız değeri (PWM kontrolü için 0-255 arası ayarlanabilir)
int turnSpeed = 75;  // Dönüş hızı
int sayac = 0;
int ref = 500;
int anlik_zaman;

void setup() {
  Serial.begin(9600);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(13, OUTPUT);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ A0, A1, A2, A3, A4, A5, A6, A7 }, sensorCount);
  qtr.setEmitterPin(2);  // Sensör LED kontrol pini (gerekirse ayarla)

  delay(500);
  Serial.println("Sensör Kalibrasyonu Başlıyor...");
  digitalWrite(13, HIGH);
  for (int i = 0; i < 50; i++) {
    qtr.calibrate();
    delay(20);
  }
  Serial.println("Kalibrasyon Tamamlandı!");
  digitalWrite(13, LOW);
  delay(2000);
}

void loop() 
{
  int position = qtr.readLineBlack(sensorValues);
  int error = position - 3500;

  if (sensorValues[7] > ref && sensorValues[6] > ref && sensorValues[5] > ref && sensorValues[4] > ref && sensorValues[3] > ref && sensorValues[2] > ref && sensorValues[1] > ref && sensorValues[0] > ref) 
  {
    
  }

  // 90 derece dönüş kontrolü
  if (sensorValues[0] > ref && sensorValues[1] > ref && sensorValues[2] > ref && sensorValues[3] > ref) {
    delay(15);
    turnRight();
    delay(70);

    do {
      qtr.read(sensorValues);
    } while (sensorValues[4] < ref);
    return;
  }

  if (sensorValues[7] > ref && sensorValues[6] > ref && sensorValues[5] > ref && sensorValues[4] > ref) {

    // Sağ 90 derece dönüş
    delay(15);
    turnLeft();
    delay(70);

    do {
      qtr.read(sensorValues);
    } while (sensorValues[3] < ref);
    return;
  }

  // PID Hesaplama
  integral += error;
  float derivative = error - lastError;
  float correction = (Kp * error) + (Ki * integral) + (Kd * derivative);
  lastError = error;

  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  // Hızları sınırla
  leftSpeed = constrain(leftSpeed, 0, 128);
  rightSpeed = constrain(rightSpeed, 0, 128);

  // Motorları çalıştır
  setMotorSpeed(leftSpeed, rightSpeed);
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  // Sol motor kontrolü (PWM ile hız ayarı)
  analogWrite(AIN1, rightSpeed);
  analogWrite(AIN2, 0);

  // Sağ motor kontrolü (PWM ile hız ayarı)
  analogWrite(BIN1, leftSpeed);
  analogWrite(BIN2, 0);
}

void turnLeft() 
{
  analogWrite(AIN1, 0);
  analogWrite(AIN2, turnSpeed);
  analogWrite(BIN1, turnSpeed);
  analogWrite(BIN2, 0);
}

void turnRight() 
{
  analogWrite(AIN1, turnSpeed);
  analogWrite(AIN2, 0);
  analogWrite(BIN1, 0);
  analogWrite(BIN2, turnSpeed);
}

void stop() 
{
  analogWrite(AIN1, 0);
  analogWrite(AIN2, 0);
  analogWrite(BIN1, 0);
  analogWrite(BIN2, 0);
}
