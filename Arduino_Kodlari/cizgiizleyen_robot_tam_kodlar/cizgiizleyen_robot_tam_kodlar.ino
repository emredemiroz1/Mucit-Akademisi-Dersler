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
float Kp = 0.035;  // Oransal kazanç (Düşürüldü - Daha yumuşak tepki)
float Ki = 0.0001; // İntegral kazanç (Aynı kaldı)
float Kd = 1.2;    // Türevsel kazanç (Artırıldı - Titremeyi ve savrulmayı söndürür)
float lastError = 0, integral = 0;
int baseSpeed = 120; // Sabit hız değeri (Düşürüldü - Viraja kontrollü giriş için)
int turnSpeed = 100; // Dönüş hızı
// ----------------------------------------------------------------------

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
    int position = qtr.readLineBlack(sensorValues);
    int error = position - 3500;
    
    // Kavşak veya tam siyah alan kontrolü
    if (sensorValues[7] > ref && sensorValues[6] > ref && sensorValues[5] > ref && sensorValues[4] > ref && sensorValues[3] > ref && sensorValues[2] > ref && sensorValues[1] > ref && sensorValues[0] > ref) 
    { 
        sayac++;
        delay(10);

        if(sayac == 1)
        {   
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

    // 90 derece dönüş kontrolleri
    if (sensorValues[0] > ref && sensorValues[1] > ref && sensorValues[2] > ref && sensorValues[3] > ref) 
    { 
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
        turnLeft();
        delay(80);
        do
        {
            qtr.read(sensorValues);
        }while(sensorValues[3] < ref);
        return;
    }
    
    // PID Hesaplama
    integral += error;
    float derivative = error - lastError;
    float correction = (Kp * error) + (Ki * integral) + (Kd * derivative);
    lastError = error;
    
    int leftSpeed = baseSpeed + correction;
    int rightSpeed = baseSpeed - correction;
    
    // Hızları sınırla (Geri basabilmesi için alt limit -255)
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);
    
    // Motorları çalıştır
    setMotorSpeed(leftSpeed, rightSpeed);
}

// Geri vites yapabilen gelişmiş motor sürme fonksiyonu
void setMotorSpeed(int leftSpeed, int rightSpeed) {
    // Sağ motor kontrolü 
    if (rightSpeed >= 0) {
        analogWrite(AIN1, rightSpeed);
        analogWrite(AIN2, 0);
    } else {
        analogWrite(AIN1, 0);
        analogWrite(AIN2, -rightSpeed);
    }
    
    // Sol motor kontrolü 
    if (leftSpeed >= 0) {
        analogWrite(BIN1, leftSpeed);
        analogWrite(BIN2, 0);
    } else {
        analogWrite(BIN1, 0);
        analogWrite(BIN2, -leftSpeed);
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