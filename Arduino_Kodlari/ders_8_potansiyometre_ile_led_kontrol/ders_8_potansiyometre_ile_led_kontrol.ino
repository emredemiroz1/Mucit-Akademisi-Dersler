// Mucit Akademisi Tekrar Notları
// Bu kodun amacı: Potansiyometre değerine göre 11, 12 ve 13 numaralı LED’leri sırayla yakmaktır.
// Pot az ise 1 LED, orta seviyede ise 2 LED, en yüksek seviyede ise 3 LED yanar.

void setup() {
  pinMode(11, OUTPUT);  // 11. LED
  pinMode(12, OUTPUT);  // 12. LED
  pinMode(13, OUTPUT);  // 13. LED
  Serial.begin(9600);   // Ekran için
}

void loop() {
  int potDeger = analogRead(A0); // 0 - 1023 arası değer
  Serial.print("Pot Degeri: ");
  Serial.println(potDeger);

  if (potDeger < 341) {
    digitalWrite(11, HIGH);  // sadece 11. LED yanar
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  } 
  else if (potDeger < 682) {
    digitalWrite(11, HIGH);  // 11 ve 12. LED yanar
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  } 
  else {
    digitalWrite(11, HIGH);  // 11, 12 ve 13. LED yanar
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
  }

  delay(200); // biraz bekle
}
