// Ders 1 - LED Hizli ve Yavas
// LED once yavas, sonra hizli yanip soner.

int led = 13;
int yavasBekleme = 1000;
int hizliBekleme = 200;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(yavasBekleme);
  digitalWrite(led, LOW);
  delay(yavasBekleme);

  digitalWrite(led, HIGH);
  delay(hizliBekleme);
  digitalWrite(led, LOW);
  delay(hizliBekleme);
}
