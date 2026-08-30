// Ders 6 - Potansiyometre ile LED Parlaklik
// A0 degeri 0-1023 arasindan 0-255 arasina cevrilir.

int potansiyometre = A0;
int led = 9;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  int potDegeri = analogRead(potansiyometre);
  int parlaklik = map(potDegeri, 0, 1023, 0, 255);

  analogWrite(led, parlaklik);
}

