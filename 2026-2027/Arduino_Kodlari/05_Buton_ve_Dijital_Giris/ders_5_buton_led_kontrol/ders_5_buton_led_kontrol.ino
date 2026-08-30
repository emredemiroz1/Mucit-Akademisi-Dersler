// Ders 5 - Buton ile LED Kontrol
// Butona basildiginda D13 LED'i yanar.

int buton = 7;
int led = 13;

void setup() {
  pinMode(buton, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  int butonDurumu = digitalRead(buton);

  if (butonDurumu == LOW) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}

