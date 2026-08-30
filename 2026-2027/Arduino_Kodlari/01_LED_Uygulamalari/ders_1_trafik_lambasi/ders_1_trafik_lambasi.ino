// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders 1 - Trafik Lambasi
// Amac: Kirmizi, sari ve yesil LED'leri trafik lambasi gibi yakmak.

int led11 = 11; // Kirmizi LED 11 numarali pine bagli.
int led12 = 12; // Sari LED 12 numarali pine bagli.
int led13 = 13; // Yesil LED 13 numarali pine bagli.

void setup() {
  // LED pinlerini cikis olarak ayarliyoruz.
  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led13, OUTPUT);
}

void loop() {
  // Kirmizi LED yanar.
  digitalWrite(led11, HIGH);
  delay(3000);
  digitalWrite(led11, LOW);

  // Sari LED yanar.
  digitalWrite(led12, HIGH);
  delay(1000);
  digitalWrite(led12, LOW);

  // Yesil LED yanar.
  digitalWrite(led13, HIGH);
  delay(3000);
  digitalWrite(led13, LOW);
}
