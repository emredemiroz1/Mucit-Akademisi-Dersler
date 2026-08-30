// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders 1 - LED Hizli ve Yavas
// Amac: LED'in once yavas, sonra hizli yanip sonmesini gormek.

int led13 = 13; // LED 13 numarali pine bagli.

void setup() {
  // LED pinini cikis olarak ayarliyoruz.
  pinMode(led13, OUTPUT);
}

void loop() {
  // LED yavas yanip soner.
  digitalWrite(led13, HIGH);
  delay(1000);
  digitalWrite(led13, LOW);
  delay(1000);

  // LED hizli yanip soner.
  digitalWrite(led13, HIGH);
  delay(200);
  digitalWrite(led13, LOW);
  delay(200);
}
