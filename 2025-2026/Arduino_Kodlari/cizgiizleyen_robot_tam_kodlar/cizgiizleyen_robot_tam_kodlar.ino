#include <QTRSensors.h>

// Motor sürücü TB6612 bağlantıları
#define AIN1 9  // Sol motor PWM
#define AIN2 10 // Sol motor PWM
#define BIN1 5  // Sağ motor PWM
#define BIN2 6  // Sağ motor PWM

// QTR-8A Sensör nesnesi
QTRSensors qtr;

const uint8_t sensorCount = 8;
uint16_t sensorValues[sensorCount];

// --- YENİ PID VE HIZ AYARLARI (Savrulmayı önlemek için güncellendi) ---
float Kp = 0.04;  // Oransal kazanç (Düşürüldü - Daha yumuşak tepki)
float Ki = 0.0001; // İntegral kazanç (Aynı kaldı)
float Kd = 1.2;    // Türevsel kazanç (Artırıldı - Titremeyi ve savrulmayı söndürür)
float lastError = 0, integral = 0;
int baseSpeed = 220; // Sabit hız değeri (Düşürüldü - Daha kararlı takip için)
int turnSpeed = 100; // Dönüş hızı
// ----------------------------------------------------------------------

int sayac = 0;
int ref = 300;

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
    // Kalibre edilmiş verileri okur (0: Beyaz, 1000: Siyah)
    int position = qtr.readLineBlack(sensorValues);
    int error = position - 3500;
    
    int siyahEsik = 700; // Siyahı algılamak için eşik değeri

    // KAVŞAK KONTROLÜ: Tüm sensörler SİYAH görüyorsa (Değerler > siyahEsik olmalı)
    if (sensorValues[7] > siyahEsik && sensorValues[6] > siyahEsik && sensorValues[5] > siyahEsik && sensorValues[4] > siyahEsik && sensorValues[3] > siyahEsik && sensorValues[2] > siyahEsik && sensorValues[1] > siyahEsik && sensorValues[0] > siyahEsik) 
    { 
        sayac++;
        delay(10); // Debounce için kısa bekleme

        if(sayac == 1)
        {   
            turnLeft();
            delay(150); // Çizgiden biraz kurtulmasını bekle
            do
            {
                // Doğru okuma fonksiyonu!
                qtr.readLineBlack(sensorValues);
            } while(sensorValues[4] < siyahEsik); // 4. sensör SİYAH görene kadar bekle
            return;
        }

        if(sayac == 2)
        {
            softRight();
            delay(150);
            do
            {
                qtr.readLineBlack(sensorValues);
            } while(sensorValues[3] < siyahEsik); 
            sayac = 0;
            return;
        }
        return;
    }

    // SAĞA 90 DERECE DÖNÜŞ: Sağdaki sensörler SİYAH görüyorsa
    // (A0'ın sağda, A7'nin solda olduğunu varsayıyoruz. Robotuna göre yönü tersine çevirmen gerekebilir)
    if (sensorValues[0] > siyahEsik && sensorValues[1] > siyahEsik && sensorValues[2] > siyahEsik && sensorValues[3] > siyahEsik) 
    { 
        turnRight();
        delay(100);
        do
        {
            qtr.readLineBlack(sensorValues);
        } while(sensorValues[4] < siyahEsik);
        return;
    }

    // SOLA 90 DERECE DÖNÜŞ: Soldaki sensörler SİYAH görüyorsa
    if (sensorValues[7] > siyahEsik && sensorValues[6] > siyahEsik && sensorValues[5] > siyahEsik && sensorValues[4] > siyahEsik) 
    { 
        turnLeft();
        delay(100);
        do
        {
            qtr.readLineBlack(sensorValues);
        } while(sensorValues[3] < siyahEsik);
        return;
    }
    
    // --- PID HESAPLAMA ---
    integral += error;
    integral = constrain(integral, -10000, 10000); // İntegral şişmesini (windup) önle

    float derivative = error - lastError;
    float correction = (Kp * error) + (Ki * integral) + (Kd * derivative);
    lastError = error;
    
    int leftSpeed = baseSpeed + correction;
    int rightSpeed = baseSpeed - correction;
    
    // Hızları sınırla
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);
    
    // Motorları çalıştır
    setMotorSpeed(leftSpeed, rightSpeed);
}

// Geri vites yapabilen gelişmiş motor sürme fonksiyonu
void setMotorSpeed(int leftSpeed, int rightSpeed) {
    // Sol motor kontrolü 
    if (leftSpeed >= 0) {
        analogWrite(AIN1, leftSpeed);
        analogWrite(AIN2, 0);
    } else {
        analogWrite(AIN1, 0);
        analogWrite(AIN2, -leftSpeed);
    }
    
    // Sağ motor kontrolü 
    if (rightSpeed >= 0) {
        analogWrite(BIN1, rightSpeed);
        analogWrite(BIN2, 0);
    } else {
        analogWrite(BIN1, 0);
        analogWrite(BIN2, -rightSpeed);
    }
}

// Alt fonksiyonlar
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