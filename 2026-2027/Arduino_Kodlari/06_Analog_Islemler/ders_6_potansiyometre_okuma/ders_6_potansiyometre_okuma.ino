// Ders 6 - Potansiyometre Okuma
// A0 pininden gelen degeri seri ekrana yazar.

int potansiyometre = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int deger = analogRead(potansiyometre);

  Serial.print("Potansiyometre degeri: ");
  Serial.println(deger);

  delay(300);
}

