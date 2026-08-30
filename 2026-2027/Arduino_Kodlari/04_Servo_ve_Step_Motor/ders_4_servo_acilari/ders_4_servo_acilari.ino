// Ders 4 - Servo Acilari
// Servo motor 0, 90 ve 180 dereceye gider.

#include <Servo.h>

Servo servoMotor;
int servoPin = 9;

void setup() {
  servoMotor.attach(servoPin);
}

void loop() {
  servoMotor.write(0);
  delay(1000);

  servoMotor.write(90);
  delay(1000);

  servoMotor.write(180);
  delay(1000);
}

