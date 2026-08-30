// Ders 9 - Cizgi Sensoru Okuma
// A0 pinindeki sensor degerini seri ekrana yazar.

int cizgiSensoru = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int deger = analogRead(cizgiSensoru);

  Serial.print("Cizgi sensoru: ");
  Serial.println(deger);

  delay(200);
}

