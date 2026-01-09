// ================= MOTOR PINLERI =================
// Benim motor sürücümde 2 motor var: sol ve sağ
// Her motorun ileri ve geri pini var
#define SOL1 5
#define SOL2 6
#define SAG1 9
#define SAG2 10

// ================= SENSOR PINLERI =================
// Sharp mesafe sensörleri analog değer veriyor (0-1023 arası okuyorum)
// Biz cm'ye çevirmiyoruz, direkt eşik ile karşılaştırıyoruz
#define SENSOR_SOL A0
#define SENSOR_SAG A1

// ================= ANAHTAR & BUTON =================
// D2 = anahtar (switch) -> ya 0 ya 1 oluyor (buton değil)
// D7 = pull-up buton -> basınca LOW olur
#define ANAHTAR_D2 2
#define BUTON_D7 7

// ================= LEDLER (BINARY) =================
// Taktik numarasını ikilik sistemle göstermek için 3 LED kullandım
// 0-7 arası sayıları gösterebiliyorum
#define LED1 11  // 1'ler basamağı
#define LED2 12  // 2'ler basamağı
#define LED3 13  // 4'ler basamağı

// ================= AYARLAR =================
int esikDeger = 325;   // sensör 325 üstüne çıkarsa "hedef var" diyorum (sahada ayarlanır)
int solHiz = 145;      // sol motorun ileri hızı
int sagHiz = 160;      // sağ motorun ileri hızı

// Seçtiğim taktik numarası (0..7)
int secim = 0;

// Seçilen taktik 1 kere çalışsın diye kullandığım bayrak
bool taktikBitti = false;

void setup() {
  // Motor pinleri çıkış
  pinMode(SOL1, OUTPUT);
  pinMode(SOL2, OUTPUT);
  pinMode(SAG1, OUTPUT);
  pinMode(SAG2, OUTPUT);

  // Sensör pinleri giriş
  pinMode(SENSOR_SOL, INPUT);
  pinMode(SENSOR_SAG, INPUT);

  // Anahtar dışarıdan 0/1 verdiği için INPUT yeterli
  pinMode(ANAHTAR_D2, INPUT);

  // Buton pull-up: basınca LOW olur
  pinMode(BUTON_D7, INPUT_PULLUP);

  // LED pinleri çıkış
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // İlk başta her şeyi durdurup LED'lerde başlangıç seçimini gösteriyorum
  dur();
  ledGoster();

  // Hakem start bekleme gibi düşün (robot 2 saniye sonra başlar)
  delay(2000);

  // Başlangıçta ekstra bir şey yapmıyorum, sadece güvenli dursun
  dur();
  delay(100);
}

void loop() {
  // ===== BUTONA BASINCA TAKTİK SEÇ =====
  // Her basışta 0..7 arasında saydırıyorum
  if (digitalRead(BUTON_D7) == LOW) {
    delay(200);  // buton zıplamasını azaltmak için

    secim++;
    if (secim > 7) secim = 0;

    // Taktik değişince LED’lerde hemen gözüksün
    ledGoster();

    // Yeni taktik seçildi -> 1 kere çalışabilsin
    taktikBitti = false;

    // 1 basış = 1 arttırsın diye buton bırakılana kadar bekliyorum
    while (digitalRead(BUTON_D7) == LOW) {}
  }

  // ===== ANAHTAR GRUBU =====
  // Anahtar LOW ise "S grubu", HIGH ise "L grubu" gibi düşünebilirim
  bool sagGrup = (digitalRead(ANAHTAR_D2) == LOW);

  // ===== 1) SEÇİLEN TAKTİĞİ 1 KERE ÇALIŞTIR =====
  // Burada taktik hareketi sadece bir kere yapılır, sonra normal sumo başlar
  if (taktikBitti == false) {

    // ===== TAKTİK 1 =====
    // S1: sağa dön + 1 saniye ileri
    if (secim == 1 && sagGrup == true) {
      taktikSagaDonIleri();
      taktikBitti = true;
    }
    // L1: sola dön + 1 saniye ileri
    else if (secim == 1 && sagGrup == false) {
      taktikSolaDonIleri();
      taktikBitti = true;
    }

    // ===== TAKTİK 2 =====
    // S2: geri kaç + sağa dön + saldır
    else if (secim == 2 && sagGrup == true) {
      taktikGeriDonSaldirSaga();
      taktikBitti = true;
    }
    // L2: geri kaç + sola dön + saldır
    else if (secim == 2 && sagGrup == false) {
      taktikGeriDonSaldirSola();
      taktikBitti = true;
    }

    // ===== TAKTİK 3 =====
    // S3: kısa ileri + sağa minik dön + tekrar ileri
    else if (secim == 3 && sagGrup == true) {
      taktikZiplatSaga();
      taktikBitti = true;
    }
    // L3: kısa ileri + sola minik dön + tekrar ileri
    else if (secim == 3 && sagGrup == false) {
      taktikZiplatSola();
      taktikBitti = true;
    }

    // Diğer seçimler için şimdilik taktik yok -> direkt sumo devam etsin
    else {
      taktikBitti = true;
    }
  }

  // ===== 2) TAKTİK BİTTİKTEN SONRA NORMAL MİDİ SUMO =====
  midiSumo();

  delay(10);  // çok küçük bekleme, sistem daha stabil oluyor
}

// ================= LED GÖSTER (0..7) =================
// Seçilen sayıyı ikilik sistemle LED’lere yazdırıyorum
void ledGoster() {
  digitalWrite(LED1, (secim & 1) ? HIGH : LOW); // 1
  digitalWrite(LED2, (secim & 2) ? HIGH : LOW); // 2
  digitalWrite(LED3, (secim & 4) ? HIGH : LOW); // 4
}

// ================= ÖRNEK TAKTİKLER =================
// Bu taktikler sadece 1 kere çalışır, sonra midi sumo devam eder

// S1: sağa dön + 1 saniye ileri
void taktikSagaDonIleri() {
  sagaDon();
  delay(450);   // yaklaşık 90 derece (sahada ayarlanır)

  ileri();
  delay(1000);

  dur();
}

// L1: sola dön + 1 saniye ileri
void taktikSolaDonIleri() {
  solaDon();
  delay(450);

  ileri();
  delay(1000);

  dur();
}

// S2: geri kaç + sağa dön + saldır
void taktikGeriDonSaldirSaga() {
  // geri git (ikisi de geri)
  analogWrite(SOL1, 0);  analogWrite(SOL2, 160);
  analogWrite(SAG1, 0);  analogWrite(SAG2, 160);
  delay(350);

  // sağa dön
  sagaDon();
  delay(300);

  // saldır
  ileri();
  delay(700);

  dur();
}

// L2: geri kaç + sola dön + saldır
void taktikGeriDonSaldirSola() {
  // geri git (ikisi de geri)
  analogWrite(SOL1, 0);  analogWrite(SOL2, 160);
  analogWrite(SAG1, 0);  analogWrite(SAG2, 160);
  delay(350);

  // sola dön
  solaDon();
  delay(300);

  // saldır
  ileri();
  delay(700);

  dur();
}

// S3: kısa ileri + sağa minik dön + tekrar ileri
void taktikZiplatSaga() {
  ileri();
  delay(250);

  sagaDon();
  delay(180);

  ileri();
  delay(500);

  dur();
}

// L3: kısa ileri + sola minik dön + tekrar ileri
void taktikZiplatSola() {
  ileri();
  delay(250);

  solaDon();
  delay(180);

  ileri();
  delay(500);

  dur();
}

// ================= MIDI SUMO MANTIĞI =================
// Sensörler hedefi görürse saldır/dön, görmezse arama
void midiSumo() {
  int solDeger = analogRead(SENSOR_SOL);
  int sagDeger = analogRead(SENSOR_SAG);

  // İkisinde de hedef varsa: direkt saldır
  if (solDeger > esikDeger && sagDeger > esikDeger) {
    ileri();
  }
  // Sadece sağ görüyorsa: sağa dön
  else if (sagDeger > esikDeger) {
    sagaDon();
  }
  // Sadece sol görüyorsa: sola dön
  else if (solDeger > esikDeger) {
    solaDon();
  }
  // Hiçbiri görmüyorsa: rakip ara
  else {
    rakipAra();
  }
}

// ================= HAREKET FONKSIYONLARI =================

void ileri() {
  // iki motor da ileri
  analogWrite(SOL1, solHiz);
  analogWrite(SOL2, 0);

  analogWrite(SAG1, sagHiz);
  analogWrite(SAG2, 0);
}

void sagaDon() {
  // sol ileri, sağ geri (yerinde sağa dön)
  analogWrite(SOL1, solHiz);
  analogWrite(SOL2, 0);

  analogWrite(SAG1, 0);
  analogWrite(SAG2, sagHiz);
}

void solaDon() {
  // sol geri, sağ ileri (yerinde sola dön)
  analogWrite(SOL1, 0);
  analogWrite(SOL2, solHiz);

  analogWrite(SAG1, sagHiz);
  analogWrite(SAG2, 0);
}

void rakipAra() {
  // yavaş sağa dönerek tarama
  analogWrite(SOL1, 90);
  analogWrite(SOL2, 0);

  analogWrite(SAG1, 0);
  analogWrite(SAG2, 70);
}

void dur() {
  // tüm motorları durdur
  analogWrite(SOL1, 0);
  analogWrite(SOL2, 0);

  analogWrite(SAG1, 0);
  analogWrite(SAG2, 0);
}
