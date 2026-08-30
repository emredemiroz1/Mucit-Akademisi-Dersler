// Motor pinlerini tanımlıyoruz
int motor1Pin1 = 5;   // Motor 1 için pin
int motor1Pin2 = 6;   // Motor 1 için pin
int motor2Pin1 = 9;   // Motor 2 için pin
int motor2Pin2 = 10;  // Motor 2 için pin

void setup() {
  // Motor pinlerini çıkış olarak ayarlıyoruz
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
}

void loop() {
  // Motorları ileri döndür (tam hız)
  analogWrite(motor1Pin1, 255); // Motor 1 ileri
  analogWrite(motor1Pin2, 0);
  analogWrite(motor2Pin1, 255); // Motor 2 ileri
  analogWrite(motor2Pin2, 0);
  delay(2000); // 2 saniye ileri

  // Motorları durdur
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, 0);
  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, 0);
  delay(1000); // 1 saniye dur

  // Motorları geri döndür (yarı hız)
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, 128); // Motor 1 geri yarı hız
  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, 128); // Motor 2 geri yarı hız
  delay(2000); // 2 saniye geri

  // Motorları durdur
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, 0);
  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, 0);
  delay(1000); // 1 saniye dur
}
