// Mucit Akademisi Tekrar Notları
// Bu kodun amacı: Potansiyometreden okunan değeri bilgisayar ekranında (Serial Monitör) göstermek.

void setup() {
  Serial.begin(9600); // Bilgisayarla haberleşmeyi başlat
}

void loop() {
  int potDeger = analogRead(A0); // Potansiyometreyi oku (0 ile 1023 arası sayı verir)
  Serial.print("Pot Degeri: ");  // Ekrana yazdır
  Serial.println(potDeger);      
  delay(500); // Yarım saniye bekle
}
