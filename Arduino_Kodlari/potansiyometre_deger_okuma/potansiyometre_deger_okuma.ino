int pot = A0; // Potansiyometrenin orta ucu A0 pinine bağlı

void setup() {
  Serial.begin(9600); // Seri monitörü başlat
}

void loop() {
  int potDeger = analogRead(pot); // Potansiyometreden değer oku (0-1023)
  Serial.println(potDeger);       // Değeri Seri Monitörde yazdır
  delay(200);                     // 0,2 saniye bekle
}
