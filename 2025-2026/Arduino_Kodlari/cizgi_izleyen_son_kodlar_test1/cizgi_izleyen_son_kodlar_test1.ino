#include <QTRSensors.h>

#define AIN1 5
#define AIN2 6
#define BIN1 9
#define BIN2 10

QTRSensors qtr;
const uint8_t sensorCount = 8;
uint16_t sensorValues[sensorCount];

float Kp = 0.04;
float Ki = 0.0001;
float Kd = 0.5;
float lastError = 0, integral = 0;

int baseSpeed = 120;
int turnSpeedFast = 180; // Keskin dönüş
int turnSpeedSlow = 120; // Hafif dönüş

void setup() 
{
    Serial.begin(9600);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);

    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, sensorCount);
    qtr.setEmitterPin(2);

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
    qtr.read(sensorValues);
    int position = qtr.readLineBlack(sensorValues);
    int error = position - 3500;

    // Keskin dönüş kontrolü (tüm sol veya sağ sensörler siyah)
    if(sensorValues[0] > 800 && sensorValues[1] > 800 && sensorValues[2] > 800 && sensorValues[3] > 800)
    {
        turnRight(true); // hızlı dönüş
        return;
    }
    if(sensorValues[4] > 800 && sensorValues[5] > 800 && sensorValues[6] > 800 && sensorValues[7] > 800)
    {
        turnLeft(true); // hızlı dönüş
        return;
    }

    // Hafif dönüş kontrolü (köşe sensörleri siyah)
    if(sensorValues[0] > 800 || sensorValues[1] > 800) { turnRight(false); return; }
    if(sensorValues[6] > 800 || sensorValues[7] > 800) { turnLeft(false); return; }

    // PID Hesaplama
    integral += error;
    float derivative = error - lastError;
    float correction = (Kp * error) + (Ki * integral) + (Kd * derivative);
    lastError = error;
    
    int leftSpeed = baseSpeed + correction;
    int rightSpeed = baseSpeed - correction;
    
    leftSpeed = constrain(leftSpeed, 0, 255);
    rightSpeed = constrain(rightSpeed, 0, 255);

    setMotorSpeed(leftSpeed, rightSpeed);
}

// Dönüş fonksiyonları
void turnLeft(bool fast)
{
    int speed = fast ? turnSpeedFast : turnSpeedSlow;
    analogWrite(AIN1, 0);
    analogWrite(AIN2, speed);
    analogWrite(BIN1, speed);
    analogWrite(BIN2, 0);
    delay(fast ? 300 : 150);
    stopMotors();
}

void turnRight(bool fast)
{
    int speed = fast ? turnSpeedFast : turnSpeedSlow;
    analogWrite(AIN1, speed);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, 0);
    analogWrite(BIN2, speed);
    delay(fast ? 300 : 150);
    stopMotors();
}

void setMotorSpeed(int leftSpeed, int rightSpeed)
{
    analogWrite(AIN1, rightSpeed);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, leftSpeed);
    analogWrite(BIN2, 0);
}

void stopMotors()
{
    analogWrite(AIN1, 0);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, 0);
    analogWrite(BIN2, 0);
}
