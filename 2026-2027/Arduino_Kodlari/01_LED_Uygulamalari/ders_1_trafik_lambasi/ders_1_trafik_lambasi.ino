// Ders 1 - Trafik Lambasi
// Kirmizi, sari ve yesil LED sirayla yanar.

int kirmiziLed = 11;
int sariLed = 12;
int yesilLed = 13;

void setup() {
  pinMode(kirmiziLed, OUTPUT);
  pinMode(sariLed, OUTPUT);
  pinMode(yesilLed, OUTPUT);
}

void loop() {
  digitalWrite(kirmiziLed, HIGH);
  delay(3000);
  digitalWrite(kirmiziLed, LOW);

  digitalWrite(sariLed, HIGH);
  delay(1000);
  digitalWrite(sariLed, LOW);

  digitalWrite(yesilLed, HIGH);
  delay(3000);
  digitalWrite(yesilLed, LOW);
}
