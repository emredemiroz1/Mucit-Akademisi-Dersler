// Tüm notaları sırayla çalma

void setup() {}

void loop() {
  tone(8, 262, 500); // Do (C4)
  delay(600);

  tone(8, 294, 500); // Re (D4)
  delay(600);

  tone(8, 330, 500); // Mi (E4)
  delay(600);

  tone(8, 349, 500); // Fa (F4)
  delay(600);

  tone(8, 392, 500); // Sol (G4)
  delay(600);

  tone(8, 440, 500); // La (A4)
  delay(600);

  tone(8, 494, 500); // Si (B4)
  delay(600);

  tone(8, 523, 800); // Do (C5) – üst oktav
  delay(1000);
}
