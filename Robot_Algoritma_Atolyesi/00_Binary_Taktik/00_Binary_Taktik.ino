// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders 1: Butona bas, sayıyı üç LED ile göster.
int led11 = 11; // 1 değerli lamba.
int led12 = 12; // 2 değerli lamba.
int led13 = 13; // 4 değerli lamba.
int buton = 7;
int sayi = 0; // Başlangıçta sayı sıfırdır.
int oncekiButon = HIGH; // INPUT_PULLUP: basılmamış buton HIGH okunur.

void setup() {
  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led13, OUTPUT);
  pinMode(buton, INPUT_PULLUP);
  // Bu derste motorları çalıştırmıyoruz.
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}

void loop() {
  int butonDurumu = digitalRead(buton); // Butonu oku.
  // Önce bırakılmış, şimdi basılmışsa yalnız bir sayı artır.
  if (butonDurumu == LOW && oncekiButon == HIGH) {
    delay(30); // Mekanik titreşimin geçmesini bekle; bu derste motorlar kapalı.
    butonDurumu = digitalRead(buton);
    if (butonDurumu == LOW) {
      sayi = sayi + 1;
      if (sayi > 7) {
        sayi = 0; // Sekizden sonra yeniden sıfıra dön.
      }
    }
  }
  // Butonu bırakırken de titreşimi süzüyoruz.
  if (butonDurumu == HIGH && oncekiButon == LOW) {
    delay(30);
    butonDurumu = digitalRead(buton);
  }
  oncekiButon = butonDurumu;
  
  // || işareti "veya" demektir. Bu sayılarda 1 değerli bit yanar.
  if (sayi == 1 || sayi == 3 || sayi == 5 || sayi == 7) {
    digitalWrite(led11, HIGH);
  } else {
    digitalWrite(led11, LOW);
  }
  // 2 değerli bit bu dört sayıda yanar.
  if (sayi == 2 || sayi == 3 || sayi == 6 || sayi == 7) {
    digitalWrite(led12, HIGH);
  } else {
    digitalWrite(led12, LOW);
  }
  // 4, 5, 6 ve 7 sayılarında 4 değerli bit yanar.
  if (sayi >= 4) {
    digitalWrite(led13, HIGH);
  } else {
    digitalWrite(led13, LOW);
  }
}
