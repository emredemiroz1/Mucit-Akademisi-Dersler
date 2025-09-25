// Motor 1 pinleri
int motor1PinA = 5; 
int motor1PinB = 6; 

// Motor 2 pinleri
int motor2PinA = 9; 
int motor2PinB = 10; 

void setup() {
  // Motor 1 pinleri çıkış
  pinMode(motor1PinA, OUTPUT);
  pinMode(motor1PinB, OUTPUT);

  // Motor 2 pinleri çıkış
  pinMode(motor2PinA, OUTPUT);
  pinMode(motor2PinB, OUTPUT);
}

void loop() {
  // 🔸 Motor 1 ileri
  digitalWrite(motor1PinA, HIGH);
  digitalWrite(motor1PinB, LOW);

  // 🔸 Motor 2 ileri
  digitalWrite(motor2PinA, HIGH);
  digitalWrite(motor2PinB, LOW);
  delay(2000);

  // Motorları durdur
  digitalWrite(motor1PinA, LOW);
  digitalWrite(motor1PinB, LOW);
  digitalWrite(motor2PinA, LOW);
  digitalWrite(motor2PinB, LOW);
  delay(1000);

  // 🔸 Motor 1 geri
  digitalWrite(motor1PinA, LOW);
  digitalWrite(motor1PinB, HIGH);

  // 🔸 Motor 2 geri
  digitalWrite(motor2PinA, LOW);
  digitalWrite(motor2PinB, HIGH);
  delay(2000);

  // Motorları durdur
  digitalWrite(motor1PinA, LOW);
  digitalWrite(motor1PinB, LOW);
  digitalWrite(motor2PinA, LOW);
  digitalWrite(motor2PinB, LOW);
  delay(1000);
}
