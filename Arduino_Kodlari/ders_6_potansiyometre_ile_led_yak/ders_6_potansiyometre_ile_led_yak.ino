// Mucit Akademisi Tekrar Notları
// Bu kodun amacı: Potansiyometre değeri belirli bir seviyeyi aşınca 12. pine bağlı LED’i yakmaktır.
// Örneğin: pot > 512 ise LED yanar, değilse söner.

void setup() {
  pinMode(12, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(A0);
  Serial.print("Pot Degeri: ");
  Serial.println(potValue);

  if (potValue > 512) {
    digitalWrite(12, HIGH); // LED yan
  } else {
    digitalWrite(12, LOW);  // LED sön
  }

  delay(200);
}
