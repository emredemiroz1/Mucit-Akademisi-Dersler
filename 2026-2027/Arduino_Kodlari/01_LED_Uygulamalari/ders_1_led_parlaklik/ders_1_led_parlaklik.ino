// Ders 1 - LED Parlaklik
// 9 numarali PWM pinindeki LED'in parlakligi artar ve azalir.

int led = 9;
int bekleme = 10;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  for (int parlaklik = 0; parlaklik <= 255; parlaklik++) {
    analogWrite(led, parlaklik);
    delay(bekleme);
  }

  for (int parlaklik = 255; parlaklik >= 0; parlaklik--) {
    analogWrite(led, parlaklik);
    delay(bekleme);
  }
}
