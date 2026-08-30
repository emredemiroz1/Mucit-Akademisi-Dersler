// Ders 4 - Step Motor Ornegi
// 4 pinli step motoru ileri ve geri dondurur.

#include <Stepper.h>

int adimSayisi = 2048;
Stepper stepMotor(adimSayisi, 8, 10, 9, 11);

void setup() {
  stepMotor.setSpeed(10);
}

void loop() {
  stepMotor.step(512);
  delay(1000);

  stepMotor.step(-512);
  delay(1000);
}

