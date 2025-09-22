// Mucit Akademisi Tekrar Notları
// Bu kodun amacı: 11, 12 ve 13 numaralı pinlere bağlı LED'leri aynı anda yakıp, 1 saniye sonra söndürmektir.

void setup() {
  //LED'leri çıkış olarak tanımla
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // LED'leri yak
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  delay(1000); // 1 saniye bekle

  // LED'leri söndür
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);

  delay(1000); // 1 saniye bekle
}
