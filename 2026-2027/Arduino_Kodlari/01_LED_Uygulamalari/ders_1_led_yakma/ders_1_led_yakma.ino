// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders 1 - LED Yakma
// Amac: 13 numarali pine bagli LED'i yakmak.
// LED'in uzun bacagi 13 numarali pine, kisa bacagi GND pinine baglanir.

int led13 = 13; // LED 13 numarali pine bagli.

void setup() {
  // pinMode komutu, pinin ne is yapacagini soyler.
  // OUTPUT: Bu pin disariya elektrik verecek demektir.
  pinMode(led13, OUTPUT);

  // HIGH komutu LED'i yakar.
  digitalWrite(led13, HIGH);
}

void loop() {
  // LED surekli yanacagi icin burada bir sey yapmiyoruz.
}
