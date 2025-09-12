// Görev 1: Her saniye kısa bip (A4 - 440 Hz)
// Basit ve ilk adım.

int buzzer = 3; // Buzzer D3 pinine bağlı, kartımızda doğrudan bağlı olduğu için yazmamıza gerek yok. 

void setup() {
  pinMode(buzzer, OUTPUT); // Buzzer çıkış pini olarak ayarlanır
}

void loop() {
  tone(buzzer, 440, 200); // 440 Hz (La), 200 ms çal
  delay(1000);            // 1 saniye bekle
}
