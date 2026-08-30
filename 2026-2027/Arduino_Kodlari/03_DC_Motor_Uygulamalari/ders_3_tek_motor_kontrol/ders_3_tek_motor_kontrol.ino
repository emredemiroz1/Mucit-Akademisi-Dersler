// Ders 3 - Tek Motor Kontrol
// Sag motoru 2 saniye calistirir, 1 saniye durdurur.

int sagMotor1 = 5;
int sagMotor2 = 6;

void setup() {
  pinMode(sagMotor1, OUTPUT);
  pinMode(sagMotor2, OUTPUT);
}

void loop() {
  digitalWrite(sagMotor1, HIGH);
  digitalWrite(sagMotor2, LOW);
  delay(2000);

  digitalWrite(sagMotor1, LOW);
  digitalWrite(sagMotor2, LOW);
  delay(1000);
}
