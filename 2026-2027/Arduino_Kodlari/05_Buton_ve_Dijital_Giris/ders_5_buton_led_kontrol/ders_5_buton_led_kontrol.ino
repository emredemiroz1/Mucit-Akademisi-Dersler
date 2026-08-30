// Ders 5 - Buton ile LED Kontrol
// Butona basildiginda D13 LED'i yanar.

int buton = 7;
int led13 = 13;

void setup() {
  pinMode(buton, INPUT_PULLUP);
  pinMode(led13, OUTPUT);
}

void loop() {
  int butonDurumu = digitalRead(buton);

  if (butonDurumu == LOW) {
    digitalWrite(led13, HIGH);
  } else {
    digitalWrite(led13, LOW);
  }
}
