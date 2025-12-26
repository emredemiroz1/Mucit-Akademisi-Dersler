// ================= MOTOR PINLERI =================
#define SOL1 5
#define SOL2 6
#define SAG1 9
#define SAG2 10

// ================= SENSOR PINLERI =================
#define SENSOR_SOL  A0
#define SENSOR_SAG  A1

// ================= taktik ANAHTARI =================
// D2: sağa çekince 0, sola çekince 1
#define taktik 2

// ================= AYARLAR =================
int esikDeger = 600;

int solHiz = 145;
int sagHiz = 160;

void setup() {
  pinMode(SOL1, OUTPUT);
  pinMode(SOL2, OUTPUT);
  pinMode(SAG1, OUTPUT);
  pinMode(SAG2, OUTPUT);

  pinMode(SENSOR_SOL, INPUT);
  pinMode(SENSOR_SAG, INPUT);

  pinMode(taktik, INPUT_PULLUP);

  // Hakem startı gibi düşün
  delay(5000);

  // ===== BAŞLANGIÇ TAKTİĞİ =====
  if (digitalRead(taktik) == LOW) {
    // Anahtar SAĞ → sağa 90 derece dön
    sagaDon();
    delay(400);   // ← 90 derece (deneyerek ayarlanır)
  } 
  else {
    // Anahtar SOL → sola 90 derece dön
    solaDon();
    delay(400);
  }

  dur();
  delay(100);
}

void loop() {
  int solDeger = analogRead(SENSOR_SOL);
  int sagDeger = analogRead(SENSOR_SAG);

  // Rakip iki sensörde de varsa → ileri saldır
  if (solDeger > esikDeger && sagDeger > esikDeger) {
    ileri();
  }
  // Rakip sağdaysa
  else if (sagDeger > esikDeger) {
    sagaDon();
  }
  // Rakip soldaysa
  else if (solDeger > esikDeger) {
    solaDon();
  }
  // Rakip yoksa → sağa dönerek ara
  else {
    sagaDon();
  }

  delay(10);
}

// ================= HAREKET FONKSIYONLARI =================

void ileri() {
  analogWrite(SOL1, solHiz);
  analogWrite(SOL2, 0);

  analogWrite(SAG1, sagHiz);
  analogWrite(SAG2, 0);
}

void sagaDon() {
  analogWrite(SOL1, solHiz);
  analogWrite(SOL2, 0);

  analogWrite(SAG1, 0);
  analogWrite(SAG2, sagHiz);
}

void solaDon() {
  analogWrite(SOL1, 0);
  analogWrite(SOL2, solHiz);

  analogWrite(SAG1, sagHiz);
  analogWrite(SAG2, 0);
}

void dur() {
  analogWrite(SOL1, 0);
  analogWrite(SOL2, 0);

  analogWrite(SAG1, 0);
  analogWrite(SAG2, 0);
}
