// Mucit Akademisi Tekrar Notları
// Bu kodun amacı: 11, 12 ve 13 numaralı pinlere bağlı LED'leri aynı anda yakıp, 
// ardından 1 saniye aralıklarla sırayla söndürmektir (önce 11, sonra 12, sonra 13).

void setup() {
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // LED'leri aynı anda yak
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  delay(1000); // 1 saniye bekle

  // LED 11 söndür
  digitalWrite(11, LOW);
  delay(1000);

  // LED 12 söndür
  digitalWrite(12, LOW);
  delay(1000);

  // LED 13 söndür
  digitalWrite(13, LOW);
  delay(1000);
}
