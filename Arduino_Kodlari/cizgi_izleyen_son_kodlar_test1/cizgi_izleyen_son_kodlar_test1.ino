#include <QTRSensors.h>

// Motor sürücü TB6612 bağlantıları
#define AIN1 5  // Sol motor PWM
#define AIN2 6  // Sol motor PWM
#define BIN1 9  // Sağ motor PWM
#define BIN2 10 // Sağ motor PWM

// QTR-8A Sensör nesnesi
QTRSensors qtr;

const uint8_t sensorCount = 8;
uint16_t sensorValues[sensorCount];

// PID Değişkenleri
float Kp = 0.04;  // Oransal kazanç
float Ki = 0.0001; // İntegral kazanç
float Kd = 0.5;   // Türevsel kazanç
float lastError = 0, integral = 0;
int baseSpeed = 120; // Sabit hız değeri (PWM kontrolü için 0-255 arası ayarlanabilir)

void setup() 
{
    Serial.begin(9600);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);

    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, sensorCount);
    qtr.setEmitterPin(2); // Sensör LED kontrol pini (gerekirse ayarla)
    
    delay(500);
    Serial.println("Sensör Kalibrasyonu Başlıyor...");
    for (int i = 0; i < 100; i++) 
    { 
        qtr.calibrate(); 
        delay(20);
    }
    Serial.println("Kalibrasyon Tamamlandı!");
}

void loop() 
{
    int position = qtr.readLineBlack(sensorValues);
    int error = position - 3500;

    // PID Hesaplama
    integral += error;
    float derivative = error - lastError;
    float correction = (Kp * error) + (Ki * integral) + (Kd * derivative);
    lastError = error;
    
    int leftSpeed = baseSpeed + correction;
    int rightSpeed = baseSpeed - correction;
    
    // Hızları sınırla
    leftSpeed = constrain(leftSpeed, 0, 255);
    rightSpeed = constrain(rightSpeed, 0, 255);
    
    // Motorları çalıştır
    setMotorSpeed(leftSpeed, rightSpeed);
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
    // Sol motor kontrolü
    analogWrite(AIN1, rightSpeed);
    analogWrite(AIN2, 0);
    
    // Sağ motor kontrolü
    analogWrite(BIN1, leftSpeed);
    analogWrite(BIN2, 0);
}
