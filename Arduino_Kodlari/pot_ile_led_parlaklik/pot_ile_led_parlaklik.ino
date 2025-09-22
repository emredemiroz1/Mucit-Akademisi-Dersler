int pot = A0;      // Potansiyometre A0’a bağlı
int led = 11;       // LED PWM pin 11' bacağına bağlı | 12 ve 13. bacaklar pwm özelliğinde
//                     olmadığından dolayı ledin parlaklığı kontrol edilemez

void setup() {
  pinMode(led, OUTPUT); // LED çıkış olarak ayarlanır
}

void loop() {
  int potDeger = analogRead(pot);          // 0 - 1023 arası değer oku
  int parlaklik = map(potDeger, 0, 1023, 0, 255); // 0-255 arası parlaklığa çevir
  analogWrite(led, parlaklik);            // LED parlaklığını ayarla
  delay(50);                               // küçük bekleme
}
