//17,04,2026 - Cuma Grubu Sumo V2
// Bu kodda 2 ana bölüm var:
// 1) Başlangıçta 2 saniye taktik seçme süresi (
//    bu süre boyunca butona basarak 8 farklı taktik seçebiliyoruz, LED'ler seçimi gösteriyor)
// 2) Savaş başladıktan sonra normal midi sumo mantığı (rakip varsa ileri, sağda rakip varsa sağa dön, solda rakip varsa sola dön, hiçbir şey yoksa rakip ara)  
// Taktikler seçildikten sonra 1 kere çalışıyor, sonra normal midi sumo devam ediyor



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

    // secim 4 için (S4 / L4)
    else if (secim == 4 && sagGrup == true) {
      taktikcumasag();        // S4
    }
    else if (secim == 4 && sagGrup == false) {
      taktikcumasol();        // L4
    }

    // secim 5 için (S5 / L5)
    else if (secim == 5 && sagGrup == true) {
      taktikHizliSaga();      // S5
    }
    else if (secim == 5 && sagGrup == false) {
      taktikHizliSola();      // L5
    }

    // secim 6 için (S6 / L6)
    else if (secim == 6 && sagGrup == true) {
      taktikIkkiTokenSaga();  // S6
    }
    else if (secim == 6 && sagGrup == false) {
      taktikIkkiTokenSola();  // L6
    }

    // secim 7 için (S7 / L7)
    else if (secim == 7 && sagGrup == true) {
      taktikGeriSonraSaga();  // S7
    }
    else if (secim == 7 && sagGrup == false) {
      taktikGeriSonraSola();  // L7
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

// S1: kısa ileri + sağa hızlı pivot + saldırı
void taktikSagaDonIleri() {
  ileri();   delay(180);
  sagaDon(); delay(300);
  ileri();   delay(900);
  dur();     delay(50);
}

// L1: kısa ileri + sola hızlı pivot + saldırı
void taktikSolaDonIleri() {
  ileri();   delay(180);
  solaDon(); delay(300);
  ileri();   delay(900);
  dur();     delay(50);
}

// S2: geri kaç + sağa dönüş + hızlı saldırı
void taktikGeriDonSaldirSaga() {
  geri();    delay(300);
  sagaDon(); delay(300);
  ileri();   delay(850);
  dur();     delay(50);
}

// L2: geri kaç + sola dönüş + hızlı saldırı
void taktikGeriDonSaldirSola() {
  geri();    delay(300);
  solaDon(); delay(300);
  ileri();   delay(850);
  dur();     delay(50);
}

// S3: feint yap + sağa dönüş + saldırı
void taktikZiplatSaga() {
  ileri();   delay(220);
  geri();    delay(150);
  sagaDon(); delay(260);
  ileri();   delay(750);
  dur();     delay(50);
}

// L3: feint yap + sola dönüş + saldırı
void taktikZiplatSola() {
  ileri();   delay(220);
  geri();    delay(150);
  solaDon(); delay(260);
  ileri();   delay(750);
  dur();     delay(50);
}

// S4: spin + açılı saldırı
void taktikcumasag() {
  sagaDon(); delay(500);
  ileri();   delay(700);
  dur();     delay(50);
}

// L4: spin + açılı saldırı
void taktikcumasol() {
  solaDon(); delay(500);
  ileri();   delay(700);
  dur();     delay(50);
}

// S5: uzun düz saldırı
void taktikHizliSaga() {
  ileri();   delay(1400);
  dur();     delay(50);
}

// L5: uzun düz saldırı
void taktikHizliSola() {
  ileri();   delay(1400);
  dur();     delay(50);
}

// S6: iki aşamalı saldırı + açılı düzeltme
void taktikIkkiTokenSaga() {
  ileri();   delay(250);
  sagaDon(); delay(250);
  ileri();   delay(250);
  solaDon(); delay(150);
  ileri();   delay(450);
  dur();     delay(50);
}

// L6: iki aşamalı saldırı + açılı düzeltme
void taktikIkkiTokenSola() {
  ileri();   delay(250);
  solaDon(); delay(250);
  ileri();   delay(250);
  sagaDon(); delay(150);
  ileri();   delay(450);
  dur();     delay(50);
}

// S7: geri kaç + hızlı sağa dönüş + saldırı
void taktikGeriSonraSaga() {
  geri();    delay(400);
  sagaDon(); delay(250);
  ileri();   delay(900);
  dur();     delay(50);
}

// L7: geri kaç + hızlı sola dönüş + saldırı
void taktikGeriSonraSola() {
  geri();    delay(400);
  solaDon(); delay(250);
  ileri();   delay(900);
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

void geri() {
  analogWrite(SOL1, 0);       analogWrite(SOL2, solHiz);
  analogWrite(SAG1, 0);       analogWrite(SAG2, sagHiz);
}

void rakipAra() {
  analogWrite(SOL1, 90);      analogWrite(SOL2, 0);
  analogWrite(SAG1, 0);       analogWrite(SAG2, 70);
}

void dur() {
  analogWrite(SOL1, 0);  analogWrite(SOL2, 0);
  analogWrite(SAG1, 0);  analogWrite(SAG2, 0);
}
