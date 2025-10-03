// Motor pinleri
#define SOL_MOTOR1 5
#define SOL_MOTOR2 6
#define SAG_MOTOR1 9
#define SAG_MOTOR2 10

// Sensör pinleri
#define SENSOR_SOL  A0
#define SENSOR_SAG  A1

// Ayarlar
#define HIZ 150      // Motor hızı
#define ESİK 500     // Sensör eşik değeri

void setup() {
  pinMode(SOL_MOTOR1, OUTPUT);
  pinMode(SOL_MOTOR2, OUTPUT);
  pinMode(SAG_MOTOR1, OUTPUT);
  pinMode(SAG_MOTOR2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Sensör değerlerini oku
  int sol = analogRead(SENSOR_SOL);
  int sag = analogRead(SENSOR_SAG);

  Serial.print("Sol: "); Serial.print(sol);
  Serial.print("  Sag: "); Serial.println(sag);

  // --- Karar verme ---
  if (sol > ESİK && sag > ESİK) {
    ileri();   // Beyaz zemin → ileri
  }
  else if (sol < ESİK && sag > ESİK) {
    sagadon(); // Sol siyah → sağa dön
  }
  else if (sag < ESİK && sol > ESİK) {
    soladon(); // Sağ siyah → sola dön
  }
  else {
    dur();     // İkisi de siyah → dur
  }

  delay(50); // Küçük bekleme
}

// ---------------- Motor Fonksiyonları ----------------

void ileri() {
  analogWrite(SOL_MOTOR1, HIZ);   
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, HIZ);   
  analogWrite(SAG_MOTOR2, 0);
}

void sagadon() {
  analogWrite(SOL_MOTOR1, HIZ);   // Sol motor ileri
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);     // Sağ motor duruyor
  analogWrite(SAG_MOTOR2, 0);
}

void soladon() {
  analogWrite(SOL_MOTOR1, 0);     // Sol motor duruyor
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, HIZ);   // Sağ motor ileri
  analogWrite(SAG_MOTOR2, 0);
}

void dur() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 0);
}
