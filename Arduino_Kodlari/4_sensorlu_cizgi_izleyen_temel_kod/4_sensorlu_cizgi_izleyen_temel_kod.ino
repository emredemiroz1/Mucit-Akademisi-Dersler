// ---------- Motor Pinleri (TB6612) ----------
#define AIN1 5   // Sol motor ileri
#define AIN2 6   // Sol motor geri
#define BIN1 9   // Sag motor ileri
#define BIN2 10  // Sag motor geri

// ---------- 4 Sensör (soldan saga) ----------
#define SENSOR_SOL      A2   // En sol
#define SENSOR_ORTA_SOL A3   // Orta sol
#define SENSOR_ORTA_SAG A4   // Orta sag
#define SENSOR_SAG      A5   // En sag

// Sensör okumaları için değişkenler
int degerSol;
int degerOrtaSol;
int degerOrtaSag;
int degerSag;

// Sensör eşik değeri
// Bu değerden BUYUKSE: SİYAH (çizgi)
// Bu değerden KUCUKSE: BEYAZ (zemin)
int esik = 500;

// Motor hızları
int ileriHiz = 1;   // Düz giderken hız
int donusHiz = 90;   // Dönerken hız

void setup() {
  // Motor pinlerini çıkış yap
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  // Sensör pinleri
  pinMode(SENSOR_SOL, INPUT);
  pinMode(SENSOR_ORTA_SOL, INPUT);
  pinMode(SENSOR_ORTA_SAG, INPUT);
  pinMode(SENSOR_SAG, INPUT);

  Serial.begin(9600);
  Serial.println("Basit 4 sensörlü cizgi izleyen basladi!");
  delay(2000);
}

void loop() {
  // --------- 1) Sensörleri oku ---------
  degerSol      = analogRead(SENSOR_SOL);
  degerOrtaSol  = analogRead(SENSOR_ORTA_SOL);
  degerOrtaSag  = analogRead(SENSOR_ORTA_SAG);
  degerSag      = analogRead(SENSOR_SAG);

  // Seri monitöre yaz (öğrenciler sensörü tanısın diye)
  Serial.print("Sol: ");       Serial.print(degerSol);
  Serial.print("  OrtaSol: "); Serial.print(degerOrtaSol);
  Serial.print("  OrtaSag: "); Serial.print(degerOrtaSag);
  Serial.print("  Sag: ");     Serial.println(degerSag);

  // --------- 2) KARAR VER ---------
  // ORTA sensörler çizgiyi görüyorsa: İLERİ GİT
  if (degerOrtaSol > esik || degerOrtaSag > esik) {
    ileri();
  }
  // Orta görmüyor, SOL sensör çizgiyi görüyorsa: SOLA DÖN
  else if (degerSol > esik) {
    solaDon();
  }
  // Orta görmüyor, SAĞ sensör çizgiyi görüyorsa: SAĞA DÖN
  else if (degerSag > esik) {
    sagaDon();
  }
  // Hiçbiri çizgiyi görmüyorsa: DUR
  else {
    dur();
  }

  delay(10); // Robot çok hızlı karar değiştirmesin diye küçük bekleme
}

// ================= MOTOR FONKSİYONLARI =================

// Düz ileri
void ileri() {
  analogWrite(AIN1, ileriHiz);  // Sol ileri
  analogWrite(AIN2, 0);

  analogWrite(BIN1, ileriHiz);  // Sag ileri
  analogWrite(BIN2, 0);
}

// Dur
void dur() {
  analogWrite(AIN1, 0);
  analogWrite(AIN2, 0);
  analogWrite(BIN1, 0);
  analogWrite(BIN2, 0);
}

// Hafif sola don (çizgi soldaysa)
void solaDon() {
  // Sol motor yavaş, sağ motor hızlı → robot SOLA kırar
  analogWrite(AIN1, donusHiz);   // Sol daha yavas
  analogWrite(AIN2, 0);

  analogWrite(BIN1, ileriHiz);   // Sag hizli
  analogWrite(BIN2, 0);
}

// Hafif saga don (çizgi sağdaysa)
void sagaDon() {
  // Sol motor hızlı, sağ motor yavaş → robot SAĞA kırar
  analogWrite(AIN1, ileriHiz);   // Sol hizli
  analogWrite(AIN2, 0);

  analogWrite(BIN1, donusHiz);   // Sag daha yavas
  analogWrite(BIN2, 0);
}
