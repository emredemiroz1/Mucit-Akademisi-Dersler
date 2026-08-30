// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders 1 - LED Parlaklik
// Amac: 9 numarali pine bagli LED'in parlakligini degistirmek.
// Not: analogWrite komutu icin 9 numarali pin kullanilir.

int led9 = 9; // LED 9 numarali pine bagli.

void setup() {
  // LED pinini cikis olarak ayarliyoruz.
  pinMode(led9, OUTPUT);
}

void loop() {
  // 0 degeri LED'i sondurur.
  analogWrite(led9, 0);
  delay(1000);

  // 80 degeri LED'i az parlak yakar.
  analogWrite(led9, 80);
  delay(1000);

  // 170 degeri LED'i daha parlak yakar.
  analogWrite(led9, 170);
  delay(1000);

  // 255 degeri LED'i en parlak yakar.
  analogWrite(led9, 255);
  delay(1000);
}
