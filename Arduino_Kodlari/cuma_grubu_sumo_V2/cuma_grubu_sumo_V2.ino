// ================= MOTOR PINLERI =================
// Benim motor sürücümde 2 motor var: sol ve sağ
// Her motorun ileri ve geri pini var
#define SOL1 5
#define SOL2 6
#define SAG1 9
#define SAG2 10

// ================= SENSOR PINLERI =================
// Sharp mesafe sensörleri analog değer veriyor
// Biz cm'ye çevirmiyoruz, direkt eşik ile karşılaştırıyoruz
#define SENSOR_SOL A0
#define SENSOR_SAG A1

// ================= ANAHTAR & BUTON =================
// D2 = anahtar (switch) -> ya 0 ya 1 oluyor
// D7 = pull-up buton -> basınca LOW olur
#define ANAHTAR_D2 2
#define BUTON_D7 7

// ================= LEDLER (BINARY) =================
// Taktik numarasını ikilik sistemle göstermek için 3 LED kullandım (0-7)
#define LED1 11  // 1
#define LED2 12  // 2
#define LED3 13  // 4

// ================= AYARLAR =================
int esikDeger = 325;   // sensör 325 üstüne çıkarsa "hedef var"
int solHiz = 145;      // sol motor ileri hızı
int sagHiz = 160;      // sağ motor ileri hızı

// Seçtiğim taktik (0..7)
int secim = 0;

// Bu değişken: robot artık savaşa başladı mı?
bool savasBasladi = false;

// Seçilen taktik sadece 1 kere çalışsın diye
bool taktikBitti = false;

void setup() {
  pinMode(SOL1, OUTPUT);
  pinMode(SOL2, OUTPUT);
  pinMode(SAG1, OUTPUT);
  pinMode(SAG2, OUTPUT);

  pinMode(SENSOR_SOL, INPUT);
  pinMode(SENSOR_SAG, INPUT);

  // Anahtar zaten 0/1 verdiği için INPUT
  pinMode(ANAHTAR_D2, INPUT);

  // Buton pull-up (basınca LOW)
  pinMode(BUTON_D7, INPUT_PULLUP);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  dur();
  ledGoster();

  // ===== 2 SANİYE TAKTİK AYARLAMA SÜRESİ =====
  // Bu süre boyunca butonla taktik seçiyorum, LED anında güncelleniyor
  unsigned long baslangic = millis();
  while (millis() - baslangic < 2000) {
    dur(); // bu modda robot kesin duracak

    if (digitalRead(BUTON_D7) == LOW) {
      delay(180); // debounce
      secim++;
      if (secim > 7) secim = 0;
      ledGoster();

      while (digitalRead(BUTON_D7) == LOW) { } // bırakana kadar bekle
    }
  }

  // 2 saniye bitti -> otomatik savaş başlıyor
  savasBasladi = true;
  taktikBitti = false; // seçili taktik 1 kere çalışacak
}

void loop() {
  // Savaş başladıktan sonra LED hep açık kalacak zaten
  // İstersen savaş sırasında taktik değişmesini de açarız.
  // Şimdilik karışmasın diye savaş sırasında butonu kullanmıyorum.

  if (!savasBasladi) {
    dur();
    return;
  }

  // Anahtar LOW ise S grubu, HIGH ise L grubu
  bool sagGrup = (digitalRead(ANAHTAR_D2) == LOW);

  // ===== 1) Önce seçilen taktiği 1 kere çalıştır =====
  if (taktikBitti == false) {

    // secim 1 için örnek (S1 / L1)
    if (secim == 1 && sagGrup == true) {
      taktikSagaDonIleri();   // S1
    }
    else if (secim == 1 && sagGrup == false) {
      taktikSolaDonIleri();   // L1
    }

    // secim 2 için örnek (S2 / L2)
    else if (secim == 2 && sagGrup == true) {
      taktikGeriDonSaldirSaga();  // S2
    }
    else if (secim == 2 && sagGrup == false) {
      taktikGeriDonSaldirSola();  // L2
    }

    // secim 3 için örnek (S3 / L3)
    else if (secim == 3 && sagGrup == true) {
      taktikZiplatSaga();     // S3
    }
    else if (secim == 3 && sagGrup == false) {
      taktikZiplatSola();     // L3
    }

    // Diğer taktikler yazılı değilse direkt midi sumo devam etsin
    taktikBitti = true;
  }

  // ===== 2) Sonra normal midi sumo =====
  midiSumo();
  delay(10);
}

// ================= LED GÖSTER (0..7) =================
void ledGoster() {
  digitalWrite(LED1, (secim & 1) ? HIGH : LOW);
  digitalWrite(LED2, (secim & 2) ? HIGH : LOW);
  digitalWrite(LED3, (secim & 4) ? HIGH : LOW);
}

// ================= TAKTİKLER (1 kere) =================

// S1: sağa dön + 1 saniye ileri
void taktikSagaDonIleri() {
  sagaDon();  delay(450);
  ileri();    delay(1000);
  dur();      delay(50);
}

// L1: sola dön + 1 saniye ileri
void taktikSolaDonIleri() {
  solaDon();  delay(450);
  ileri();    delay(1000);
  dur();      delay(50);
}

// S2: geri kaç + sağa dön + saldır
void taktikGeriDonSaldirSaga() {
  analogWrite(SOL1, 0);  analogWrite(SOL2, 160);
  analogWrite(SAG1, 0);  analogWrite(SAG2, 160);
  delay(350);

  sagaDon(); delay(300);
  ileri();   delay(700);
  dur();     delay(50);
}

// L2: geri kaç + sola dön + saldır
void taktikGeriDonSaldirSola() {
  analogWrite(SOL1, 0);  analogWrite(SOL2, 160);
  analogWrite(SAG1, 0);  analogWrite(SAG2, 160);
  delay(350);

  solaDon(); delay(300);
  ileri();   delay(700);
  dur();     delay(50);
}

// S3: kısa ileri + sağa minik dön + tekrar ileri
void taktikZiplatSaga() {
  ileri();   delay(250);
  sagaDon(); delay(180);
  ileri();   delay(500);
  dur();     delay(50);
}

// L3: kısa ileri + sola minik dön + tekrar ileri
void taktikZiplatSola() {
  ileri();   delay(250);
  solaDon(); delay(180);
  ileri();   delay(500);
  dur();     delay(50);
}

// ================= MIDI SUMO MANTIĞI =================
void midiSumo() {
  int solDeger = analogRead(SENSOR_SOL);
  int sagDeger = analogRead(SENSOR_SAG);

  if (solDeger > esikDeger && sagDeger > esikDeger) {
    ileri();
  }
  else if (sagDeger > esikDeger) {
    sagaDon();
  }
  else if (solDeger > esikDeger) {
    solaDon();
  }
  else {
    rakipAra();
  }
}

// ================= HAREKET FONKSIYONLARI =================
void ileri() {
  analogWrite(SOL1, solHiz);  analogWrite(SOL2, 0);
  analogWrite(SAG1, sagHiz);  analogWrite(SAG2, 0);
}

void sagaDon() {
  analogWrite(SOL1, solHiz);  analogWrite(SOL2, 0);
  analogWrite(SAG1, 0);       analogWrite(SAG2, sagHiz);
}

void solaDon() {
  analogWrite(SOL1, 0);       analogWrite(SOL2, solHiz);
  analogWrite(SAG1, sagHiz);  analogWrite(SAG2, 0);
}

void rakipAra() {
  analogWrite(SOL1, 90);      analogWrite(SOL2, 0);
  analogWrite(SAG1, 0);       analogWrite(SAG2, 70);
}

void dur() {
  analogWrite(SOL1, 0);  analogWrite(SOL2, 0);
  analogWrite(SAG1, 0);  analogWrite(SAG2, 0);
}
