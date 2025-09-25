// Pin isimlendirme örneği
int motorPinA = 5; // motorPinA => Arduino D5
int motorPinB = 6; // motorPinB => Arduino D6

void setup() {
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
}

void loop() {
  // motor ileri
  digitalWrite(motorPinA, HIGH);
  digitalWrite(motorPinB, LOW);
  delay(3000);

  // dur
  digitalWrite(motorPinA, LOW);
  digitalWrite(motorPinB, LOW);
  delay(1000);
}
