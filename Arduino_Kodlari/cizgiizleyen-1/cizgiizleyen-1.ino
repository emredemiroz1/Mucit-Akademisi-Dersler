#include <QTRSensors.h>
// Motor sürücü TB6612 bağlantıları
#define AIN1 5   // Sol motor PWM
#define AIN2 6   // Sol motor PWM
#define BIN1 9   // Sağ motor PWM
#define BIN2 10  // Sağ motor PWM

// QTR-8A Sensör nesnesi
QTRSensors qtr;
const uint8_t sensorCount = 8;
uint16_t sensorValues[sensorCount];

// PID Değişkenleri
float Kp = 0.08;     // Oransal kazanç
float Ki = 0.00001;  // İntegral kazanç
float Kd = 0.5;      // Türevsel kazanç
float lastError = 0, integral = 0;

int baseSpeed = 80;   // Sabit hız değeri (PWM kontrolü için 0-255 arası ayarlanabilir)
int turnSpeed = 60;   // Dönüş hızı
int sayac = 0;
int ref = 600;