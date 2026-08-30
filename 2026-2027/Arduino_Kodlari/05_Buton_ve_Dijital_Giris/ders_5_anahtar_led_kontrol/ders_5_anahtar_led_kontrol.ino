// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders 5 - Anahtar ile LED Kontrol
// Amac: D4 pinindeki anahtar ile D13 LED'ini kontrol etmek.
// ROBOMER kartta anahtar D4 pinine baglidir.

int anahtar4 = 4; // Anahtar 4 numarali pine bagli.
int led13 = 13;  // LED 13 numarali pine bagli.

void setup() {
  // Anahtar pinini giris olarak ayarliyoruz.
  pinMode(anahtar4, INPUT_PULLUP);

  // LED pinini cikis olarak ayarliyoruz.
  pinMode(led13, OUTPUT);
}

void loop() {
  // Anahtarin durumunu okuyoruz.
  int anahtarDurumu = digitalRead(anahtar4);

  // Anahtar acik ise LED yanar.
  if (anahtarDurumu == LOW) {
    digitalWrite(led13, HIGH);
  } else {
    digitalWrite(led13, LOW);
  }
}
