// Ders 1 - LED Yakma
// 13 numarali pine bagli LED surekli yanar.

int led = 13;

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}

void loop() {
  // LED surekli yanacagi icin loop bolumunde bir sey yapmiyoruz.
}
