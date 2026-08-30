// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders 2 - Buzzer Caldirma
// Amac: D3 pinine bagli buzzer'i caldirmak ve susturmak.

int buzzer3 = 3; // Buzzer D3 pinine bagli.

void setup() {
  // Buzzer pinini cikis olarak ayarliyoruz.
  pinMode(buzzer3, OUTPUT);
}

void loop() {
  // HIGH komutu buzzer'i caldirir.
  digitalWrite(buzzer3, HIGH);
  delay(500);

  // LOW komutu buzzer'i susturur.
  digitalWrite(buzzer3, LOW);
  delay(500);
}
