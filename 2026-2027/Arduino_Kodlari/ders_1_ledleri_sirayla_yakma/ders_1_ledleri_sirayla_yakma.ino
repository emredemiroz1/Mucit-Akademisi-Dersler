// Ders 1 - LEDleri Sirayla Yakma
// 11, 12 ve 13 numarali pinlerdeki LED'ler sirayla yanar.

int ledler[] = {11, 12, 13};
int ledSayisi = 3;
int beklemeSuresi = 500;

void setup() {
  for (int i = 0; i < ledSayisi; i++) {
    pinMode(ledler[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < ledSayisi; i++) {
    digitalWrite(ledler[i], HIGH);
    delay(beklemeSuresi);
    digitalWrite(ledler[i], LOW);
  }
}
