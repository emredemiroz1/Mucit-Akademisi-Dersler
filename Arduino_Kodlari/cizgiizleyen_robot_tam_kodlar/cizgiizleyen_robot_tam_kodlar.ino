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
int baseSpeed = 200; // Sabit hız değeri (PWM kontrolü için 0-255 arası ayarlanabilir)
int turnSpeed = 100; // Dönüş hızı
int sayac = 0;
int ref = 500;

void setup() 
{
    Serial.begin(9600);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(13, OUTPUT);
    
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
    
    if (sensorValues[7]  > ref && sensorValues[6] > ref && sensorValues[5] > ref && sensorValues[4] > ref && sensorValues[3] > ref && sensorValues[2] > ref && sensorValues[1] > ref && sensorValues[0] > ref) 
    { 
        sayac++;
        delay(10);

        if(sayac == 1)
        {   
            // Sol 90 derece dönüş
            turnLeft();
            delay(100);

            do
            {
                qtr.read(sensorValues);
            }while(sensorValues[4] > ref);
            return;
        }

        if(sayac == 2)
        {
            softRight();
            delay(100);

            do
            {
                qtr.read(sensorValues);
            }while(sensorValues[3] > ref);
            sayac = 0;
            return;
        }
        return;
    }

    // 90 derece dönüş kontrolü
    if (sensorValues[0] > ref && sensorValues[1] > ref && sensorValues[2] > ref && sensorValues[3] > ref) 
    { 
        // Sol 90 derece dönüş
        turnRight();
        delay(80);

        do
        {
            qtr.read(sensorValues);
        }while(sensorValues[4] < ref);
        return;
    }

    if (sensorValues[7] > ref && sensorValues[6] > ref && sensorValues[5] > ref && sensorValues[4] > ref) 
    { 
        // Sağ 90 derece dönüş
        turnLeft();
        delay(80);

        do
        {
            qtr.read(sensorValues);
        }while(sensorValues[3] < ref);
        return;
    }

    if (sensorValues[7] < 800 && sensorValues[6] < 800 && sensorValues[5] < 800 && sensorValues[4] < 800 && sensorValues[3] < 800 && sensorValues[2] < 800 && sensorValues[1] < 800 && sensorValues[0] < 800) 
    { 
        integral = 0;  // Entegral birikmesini sıfırla
        lastError = 0; // Önceki hatayı sıfırla
    //    setMotorSpeed(0, 0); // Motorları durdur
    //    delay(100);
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
    leftSpeed = constrain(leftSpeed, 0, 255);
    rightSpeed = constrain(rightSpeed, 0, 255);
    
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

void softRight()
{
    analogWrite(AIN1, turnSpeed);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, 0);
    analogWrite(BIN2, turnSpeed);
    delay(150);
    analogWrite(AIN1, turnSpeed);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, 50);
    analogWrite(BIN2, 0);
}

void softLeft()
{
    analogWrite(AIN1, 50);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, turnSpeed);
    analogWrite(BIN2, 0);
}

void wait()
{
    analogWrite(AIN1, 0);
    analogWrite(AIN2, 0);
    analogWrite(BIN1, 0);
    analogWrite(BIN2, 0);
}
