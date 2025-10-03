// Motor pinlerini tanımlıyoruz
#define SOL_MOTOR1 5
#define SOL_MOTOR2 6
#define SAG_MOTOR1 9
#define SAG_MOTOR2 10

// Sensör pinimiz
int sensorPin = A0;
int deger = 0;           // Sensörden gelen değer
int esikDeger = 250;     // Siyah ve beyazı ayırmak için eşik

// ---------------- MOTOR HAREKETLERİ ----------------
void ileri() {
  analogWrite(SOL_MOTOR1, 150);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 150);
  analogWrite(SAG_MOTOR2, 0);
}

void dur() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 0);
}
// ---------------------------------------------------

void setup() {
  // Motor pinlerini çıkış olarak ayarlıyoruz
  pinMode(SOL_MOTOR1, OUTPUT);
  pinMode(SOL_MOTOR2, OUTPUT);
  pinMode(SAG_MOTOR1, OUTPUT);
  pinMode(SAG_MOTOR2, OUTPUT);

  pinMode(sensorPin, INPUT);  // Sensör girişi
  Serial.begin(9600);         // Bilgisayara veri göndermek için
}

void loop() {
  deger = analogRead(sensorPin);  // Sensör değeri oku
  Serial.println(deger);          // Bilgisayara yazdır

  if (deger > esikDeger) {
    dur();        // Siyah çizgiyi gördüyse DUR
  } else {
    ileri();      // Beyaz zemindeyse İLERİ
  }
}
