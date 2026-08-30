// Adım 3 - Hızı artırıp azaltma (ileri yönde)
int motorPinA = 5; // PWM destekleyen pin (Nano'da D5 PWM vardır)
int motorPinB = 6;

void setup() {
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
  digitalWrite(motorPinB, LOW); // geri pin kapalı
}

void loop() {
  // Hızı kademeli artır
  for (int speed = 0; speed <= 255; speed += 10) {
    analogWrite(motorPinA, speed); // speed arttıkça motor hızlanır
    delay(100); // ufak bekleme
  }

  // Hızı yavaşlat
  for (int speed = 255; speed >= 0; speed -= 10) {
    analogWrite(motorPinA, speed);
    delay(100);
  }

  analogWrite(motorPinA, 0); // tamamen dur
  delay(500);
}
