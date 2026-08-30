// Ders 3 - Motor Hiz Kontrol
// Sag motor once yavas, sonra hizli calisir.

int sagMotor1 = 5;
int sagMotor2 = 6;

void setup() {
  pinMode(sagMotor1, OUTPUT);
  pinMode(sagMotor2, OUTPUT);
}

void loop() {
  analogWrite(sagMotor1, 100);
  digitalWrite(sagMotor2, LOW);
  delay(2000);

  analogWrite(sagMotor1, 220);
  digitalWrite(sagMotor2, LOW);
  delay(2000);

  digitalWrite(sagMotor1, LOW);
  digitalWrite(sagMotor2, LOW);
  delay(1000);
}
