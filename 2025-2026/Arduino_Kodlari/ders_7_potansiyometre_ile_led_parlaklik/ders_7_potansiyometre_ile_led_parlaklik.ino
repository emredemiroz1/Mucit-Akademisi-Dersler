// Mucit Akademisi Tekrar Notları
// Bu kodun amacı: Potansiyometreyi çevirerek LED’in parlaklığını ayarlamaktır.

void setup() {
  pinMode(11, OUTPUT);   // 11 numaralı pine bağlı LED
  Serial.begin(9600);    // Ekrana yazdırmak için
}

void loop() {
  int potDeger = analogRead(A0);               // Pot değeri 0 - 1023 arası
  int ledParlaklik = map(potDeger, 0, 1023, 0, 255); // 0 - 255 arası dönüştür
  analogWrite(11, ledParlaklik);               // LED parlaklığı ayarlanır

  Serial.print("Pot: ");
  Serial.print(potDeger);
  Serial.print(" -> LED Parlaklik: ");
  Serial.println(ledParlaklik);

  delay(200);
}
