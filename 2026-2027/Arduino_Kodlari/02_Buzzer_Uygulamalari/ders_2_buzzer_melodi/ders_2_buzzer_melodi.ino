// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders 2 - Buzzer Melodi
// Amac: D3 pinine bagli buzzer ile basit sesler calmak.
// tone komutu buzzer'dan ses cikarmak icin kullanilir.

int buzzer3 = 3; // Buzzer D3 pinine bagli.

void setup() {
  // Buzzer pinini cikis olarak ayarliyoruz.
  pinMode(buzzer3, OUTPUT);
}

void loop() {
  // Birinci ses calar.
  tone(buzzer3, 262);
  delay(300);
  noTone(buzzer3);
  delay(200);

  // Ikinci ses calar.
  tone(buzzer3, 330);
  delay(300);
  noTone(buzzer3);
  delay(200);

  // Ucuncu ses calar.
  tone(buzzer3, 392);
  delay(300);
  noTone(buzzer3);
  delay(200);

  // Melodi bittikten sonra biraz bekler.
  delay(1000);
}
