// Ders 8 - Temel Robot Hareketleri
// Robot ileri, geri, saga, sola hareket eder ve durur.

int sagMotor1 = 5;
int sagMotor2 = 6;
int solMotor1 = 9;
int solMotor2 = 10;
int hiz = 180;

void setup() {
  pinMode(sagMotor1, OUTPUT);
  pinMode(sagMotor2, OUTPUT);
  pinMode(solMotor1, OUTPUT);
  pinMode(solMotor2, OUTPUT);
}

void loop() {
  ileri();
  delay(2000);

  geri();
  delay(2000);

  sagaDon();
  delay(1000);

  solaDon();
  delay(1000);

  dur();
  delay(2000);
}

void ileri() {
  analogWrite(sagMotor1, hiz);
  digitalWrite(sagMotor2, LOW);
  analogWrite(solMotor1, hiz);
  digitalWrite(solMotor2, LOW);
}

void geri() {
  digitalWrite(sagMotor1, LOW);
  analogWrite(sagMotor2, hiz);
  digitalWrite(solMotor1, LOW);
  analogWrite(solMotor2, hiz);
}

void sagaDon() {
  digitalWrite(sagMotor1, LOW);
  analogWrite(sagMotor2, hiz);
  analogWrite(solMotor1, hiz);
  digitalWrite(solMotor2, LOW);
}

void solaDon() {
  analogWrite(sagMotor1, hiz);
  digitalWrite(sagMotor2, LOW);
  digitalWrite(solMotor1, LOW);
  analogWrite(solMotor2, hiz);
}

void dur() {
  digitalWrite(sagMotor1, LOW);
  digitalWrite(sagMotor2, LOW);
  digitalWrite(solMotor1, LOW);
  digitalWrite(solMotor2, LOW);
}
