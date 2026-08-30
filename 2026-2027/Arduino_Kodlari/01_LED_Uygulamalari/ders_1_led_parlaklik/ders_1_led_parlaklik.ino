// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders 1 - LED Parlaklik
// Amac: 11 numarali pine bagli LED'in parlakligini degistirmek.
// ROBOMER kartta LED'ler 11, 12 ve 13 numarali pinlerdedir.

int led11 = 11; // LED 11 numarali pine bagli.

void setup() {
  // LED pinini cikis olarak ayarliyoruz.
  pinMode(led11, OUTPUT);
}

void loop() {
  // 0 degeri LED'i sondurur.
  analogWrite(led11, 0);
  delay(1000);

  // 80 degeri LED'i az parlak yakar.
  analogWrite(led11, 80);
  delay(1000);

  // 170 degeri LED'i daha parlak yakar.
  analogWrite(led11, 170);
  delay(1000);

  // 255 degeri LED'i en parlak yakar.
  analogWrite(led11, 255);
  delay(1000);
}
