int pot = A0;      // Potansiyometre A0'a bağlı
int buzzer = 3;    // Buzzer D3’e bağlı

void setup() {
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int potDeger = analogRead(pot);                     // potansiyometreden oku
  int frekans = map(potDeger, 0, 1023, 100, 2000);    // 100-2000 Hz arası
  tone(buzzer, frekans, 200);                         // seçilen frekansı 200 ms çal
  delay(250);                                         // kısa bekle
}
