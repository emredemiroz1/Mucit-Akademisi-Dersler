// Mucit Akademisi Tekrar Notları
// Bu kodun amacı: 3 numaralı pine bağlı buzzer'ı 1 saniye boyunca çalıştırmak ve sonra susturmaktır.

void setup() {
  pinMode(3, OUTPUT);
}

void loop() {
  // Buzzer çalışsın
  digitalWrite(3, HIGH);
  delay(1000); // 1 saniye ses çıkarır

  // Buzzer kapansın
  digitalWrite(3, LOW);
  delay(1000); // 1 saniye sessizlik
}
