// ====== LED PINLERI ======
#define LED1 11   // en düşük bit (1)
#define LED2 12   // orta bit (2)
#define LED3 13   // en yüksek bit (4)

// ====== BUTON PINI ======
#define BUTON 7   // pull-up buton (basınca LOW olur)

int sayi = 0;     // 0-7 arası dönecek

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  pinMode(BUTON, INPUT_PULLUP); // çok önemli

  ledGoster();
}

void loop() {
  // Butona basıldı mı?
  if (digitalRead(BUTON) == LOW) {
    delay(200); // buton zıplamasını azaltır

    // sayıyı artır
    sayi++;
    if (sayi > 7) sayi = 0;

    ledGoster();

    // buton bırakılana kadar bekle (1 basış = 1 artırma)
    while (digitalRead(BUTON) == LOW) { }
  }
}

// Sayıyı ikilik sistemle LED'lere yazdır
void ledGoster() {
  digitalWrite(LED1, (sayi & 1) ? HIGH : LOW); // 1'ler biti
  digitalWrite(LED2, (sayi & 2) ? HIGH : LOW); // 2'ler biti
  digitalWrite(LED3, (sayi & 4) ? HIGH : LOW); // 4'ler biti
}
