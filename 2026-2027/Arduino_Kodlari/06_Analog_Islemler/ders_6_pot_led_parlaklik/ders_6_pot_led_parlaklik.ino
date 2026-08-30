// Ders 6 - Potansiyometre ile LED Parlaklik
// A0 degeri 0-1023 arasindan 0-255 arasina cevrilir.
// ROBOMER kartta LED'ler 11, 12 ve 13 numarali pinlerdedir.

int potansiyometre = A0;
int led11 = 11;

void setup() {
  pinMode(led11, OUTPUT);
}

void loop() {
  int potDegeri = analogRead(potansiyometre);
  int parlaklik = map(potDegeri, 0, 1023, 0, 255);

  analogWrite(led11, parlaklik);
}
