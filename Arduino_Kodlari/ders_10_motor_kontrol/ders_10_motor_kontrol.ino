// Basit - doğrudan pin numaralarıyla
void setup() {
  pinMode(5, OUTPUT); // 5 numaralı pini çıkış yap
  pinMode(6, OUTPUT); // 6 numaralı pini çıkış yap
}

void loop() {
  digitalWrite(5, HIGH); // 5 numaralı pin HIGH -> motor çalışır
  digitalWrite(6, LOW);  // 6 numaralı pin LOW
  delay(3000);           // 3 saniye dönsün

  // durdur
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  delay(1000); // 1 saniye bekle
}
