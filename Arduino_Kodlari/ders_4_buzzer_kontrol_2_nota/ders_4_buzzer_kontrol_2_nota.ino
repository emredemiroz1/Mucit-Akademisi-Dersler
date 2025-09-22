// Mucit Akademisi Tekrar Notları
// Bu kodun amacı: 3 numaralı pine bağlı buzzer ile farklı notaları süre belirterek çalmaktır.
// tone(pin, frekans, süre) → buzzer'dan belirli frekansta sesi verilen süre boyunca çıkarır.
// Örneğin: tone(3, 343, 250); → 343 Hz frekansta sesi 250 ms boyunca çalar.

void setup() {
  pinMode(3, OUTPUT);
}

void loop() {
  // DO (C) notası
  tone(3, 262, 500);   // 262 Hz → 500 ms boyunca çalar
  delay(600);          // notadan biraz uzun bekleme (kesik kesik duyulsun)

  // RE (D) notası
  tone(3, 294, 500);   // 294 Hz → 500 ms
  delay(600);

  // Mİ (E) notası
  tone(3, 330, 500);   // 330 Hz → 500 ms
  delay(600);
}
