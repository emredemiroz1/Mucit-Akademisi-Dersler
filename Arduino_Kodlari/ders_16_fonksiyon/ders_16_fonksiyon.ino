// Motor pinlerini tanımlıyoruz
#define SOL_MOTOR1 5   // Sol motorun birinci pini
#define SOL_MOTOR2 6   // Sol motorun ikinci pini
#define SAG_MOTOR1 9   // Sağ motorun birinci pini
#define SAG_MOTOR2 10  // Sağ motorun ikinci pini

void setup() {
  // Motor pinlerini çıkış olarak ayarlıyoruz
  pinMode(SOL_MOTOR1, OUTPUT);
  pinMode(SOL_MOTOR2, OUTPUT);
  pinMode(SAG_MOTOR1, OUTPUT);
  pinMode(SAG_MOTOR2, OUTPUT);
}

void loop() {
  // 1) İleri git
  ileri();
  delay(1000);

  // 2) Dur
  dur();
  delay(1000);

  // 3) Geri git
  geri();
  delay(1000);

  // 4) Sağa dön
  sag();
  delay(1000);

  // 5) Sola dön
  sol();
  delay(1000);
}

// ----------------- Fonksiyonlar -----------------

void ileri() {
  analogWrite(SOL_MOTOR1, 150);   // Sol motor ileri
  analogWrite(SOL_MOTOR2, 0);

  analogWrite(SAG_MOTOR1, 150);   // Sağ motor ileri
  analogWrite(SAG_MOTOR2, 0);
}

void geri() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 150);   // Sol motor geri

  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 150);   // Sağ motor geri
}

void sag() {
  analogWrite(SOL_MOTOR1, 150);   // Sol motor ileri
  analogWrite(SOL_MOTOR2, 0);

  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 150);   // Sağ motor geri
}

void sol() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 150);   // Sol motor geri

  analogWrite(SAG_MOTOR1, 150);   // Sağ motor ileri
  analogWrite(SAG_MOTOR2, 0);
}

void dur() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 0);
}
