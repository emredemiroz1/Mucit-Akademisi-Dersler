// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders 1 - LEDleri Sirayla Yakma
// Amac: 11, 12 ve 13 numarali pinlerdeki LED'leri sirayla yakmak.
// LED'lerin kisa bacaklari GND pinine baglanir.

int led11 = 11; // Birinci LED 11 numarali pine bagli.
int led12 = 12; // Ikinci LED 12 numarali pine bagli.
int led13 = 13; // Ucuncu LED 13 numarali pine bagli.

void setup() {
  // LED pinlerini cikis olarak ayarliyoruz.
  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led13, OUTPUT);
}

void loop() {
  // Once 11 numarali pine bagli LED yanar.
  digitalWrite(led11, HIGH);
  delay(500);
  digitalWrite(led11, LOW);

  // Sonra 12 numarali pine bagli LED yanar.
  digitalWrite(led12, HIGH);
  delay(500);
  digitalWrite(led12, LOW);

  // Son olarak 13 numarali pine bagli LED yanar.
  digitalWrite(led13, HIGH);
  delay(500);
  digitalWrite(led13, LOW);
}
