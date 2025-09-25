// Adım 2 - İleri, dur, geri
int motorPinA = 5;
int motorPinB = 6;

void setup() {
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
}

void loop() {
  // İleri
  digitalWrite(motorPinA, HIGH);
  digitalWrite(motorPinB, LOW);
  delay(2000); // 2s ileri

  // Dur
  digitalWrite(motorPinA, LOW);
  digitalWrite(motorPinB, LOW);
  delay(1000); // 1s dur

  // Geri
  digitalWrite(motorPinA, LOW);
  digitalWrite(motorPinB, HIGH);
  delay(2000); // 2s geri

  // Dur
  digitalWrite(motorPinA, LOW);
  digitalWrite(motorPinB, LOW);
  delay(1000);
}
