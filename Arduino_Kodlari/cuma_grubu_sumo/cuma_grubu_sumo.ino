// ================= MOTOR PINLERI =================
#define SOL1 5
#define SOL2 6
#define SAG1 9
#define SAG2 10

// ================= SENSOR PINLERI =================
#define SENSOR_SOL  A0
#define SENSOR_SAG  A1

// ================= ANAHTAR & BUTON =================
#define ANAHTAR_D2 2
#define BUTON_D7   7   // pull-up buton

// ================= LEDLER (BINARY) =================
#define LED1 11
#define LED2 12
#define LED3 13

// ================= AYARLAR =================
int esikDeger = 325;
int solHiz = 145;
int sagHiz = 160;

// Seçilen taktik numarası: 0..7
int secim = 0;

// Taktik 1 kere çalışsın diye
bool taktikBitti = false;

void setup() {
  pinMode(SOL1, OUTPUT);  pinMode(SOL2, OUTPUT);
  pinMode(SAG1, OUTPUT);  pinMode(SAG2, OUTPUT);

  pinMode(SENSOR_SOL, INPUT);
  pinMode(SENSOR_SAG, INPUT);

  pinMode(ANAHTAR_D2, INPUT_PULLUP);
  pinMode(BUTON_D7, INPUT_PULLUP);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  dur();
  ledGoster();

  delay(2000); // hakem start bekleme

  // İstersen bu sabit açılışı da kaldırabiliriz
  dur();
  delay(100);
}

void loop() {
  // ===== BUTONA BASINCA TAKTİK SEÇ =====
  if (digitalRead(BUTON_D7) == LOW) {
    delay(200);
    secim++;
    if (secim > 7) secim = 0;
    ledGoster();

    taktikBitti = false; // yeni seçim -> taktik tekrar 1 kere çalışabilir

    while (digitalRead(BUTON_D7) == LOW) { }
  }

  // Grup: D2 LOW ise S grubu, HIGH ise L grubu
  bool sagGrup = (digitalRead(ANAHTAR_D2) == LOW);

  // ===== 1) ÖNCE SEÇİLEN TAKTİĞİ 1 KERE ÇALIŞTIR =====
  if (taktikBitti == false) {
    // Örnek: sadece "1" için iki farklı taktik gösteriyoruz
    if (secim == 1 && sagGrup == true) {
      taktikSagaDonIleri();
      taktikBitti = true;
    }
    else if (secim == 1 && sagGrup == false) {
      taktikSolaDonIleri();
      taktikBitti = true;
    }
    else {
      // Diğer seçimler için şimdilik taktik yok -> direkt midi sumo'ya geç
      taktikBitti = true;
    }
  }

  // ===== 2) TAKTİK BİTTİKTEN SONRA HEP MIDI SUMO =====
  midiSumo();

  delay(10);
}

// ================= LED GÖSTER (0..7) =================
void ledGoster() {
  digitalWrite(LED1, (secim & 1) ? HIGH : LOW);
  digitalWrite(LED2, (secim & 2) ? HIGH : LOW);
  digitalWrite(LED3, (secim & 4) ? HIGH : LOW);
}

// ================= ÖRNEK TAKTİKLER =================
void taktikSagaDonIleri() {
  sagaDon();
  delay(450);
  ileri();
  delay(1000);
  dur();
}

void taktikSolaDonIleri() {
  solaDon();
  delay(450);
  ileri();
  delay(1000);
  dur();
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
