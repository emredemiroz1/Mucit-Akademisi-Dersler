// Ders 2 - Buzzer Melodi
// D3 pinindeki buzzer ile kisa bir melodi calar.

int buzzer = 3;

int notalar[] = {262, 294, 330, 349, 392, 440, 494, 523};
int notaSayisi = 8;
int notaSuresi = 300;

void setup() {
  pinMode(buzzer, OUTPUT);
}

void loop() {
  for (int i = 0; i < notaSayisi; i++) {
    tone(buzzer, notalar[i]);
    delay(notaSuresi);
    noTone(buzzer);
    delay(100);
  }

  delay(1000);
}

