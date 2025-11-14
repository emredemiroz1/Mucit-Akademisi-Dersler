// ---------- Motor Pinleri (Önceki kodunuzla aynı) ----------
#define SOL_MOTOR1 5
#define SOL_MOTOR2 6
#define SAG_MOTOR1 9
#define SAG_MOTOR2 10

// ---------- Mesafe Sensörü (Ön tarafta tek sensör) ----------
#define MESAFE_SENSOR A0   // A0'a bağlı mesafe sensörü

// Mesafe sensörü değeri ve eşik
int mesafeDegeri = 0;
int esikDegeri = 500;   // 500 üzeri = ENGEL YAKIN, altı = GÜVENLİ (sensörüne göre değişebilir)

void setup() {
  // Motor pinlerini çıkış olarak ayarla
  pinMode(SOL_MOTOR1, OUTPUT);
  pinMode(SOL_MOTOR2, OUTPUT);
  pinMode(SAG_MOTOR1, OUTPUT);
  pinMode(SAG_MOTOR2, OUTPUT);

  // Mesafe sensör pini
  pinMode(MESAFE_SENSOR, INPUT);
  
  Serial.begin(9600);
  Serial.println("=== Sistem Basladi ===");
  Serial.println("Mod: Engelden Kacan Robot");
  Serial.print("Esik Degeri: ");
  Serial.println(esikDegeri);
  
  // Robota baslamak için 3 saniye bekleme süresi
  Serial.println("Baslamak icin 3 saniye...");
  delay(3000);
  Serial.println("BASLA!");
}

void loop() {
  // Mesafe sensöründen değeri oku
  mesafeDegeri = analogRead(MESAFE_SENSOR);

  // Sensör değerini seri porta yazdır (hata ayıklama için)
  Serial.print("Mesafe Sensörü: ");
  Serial.println(mesafeDegeri);

  // ---------- Hareket Mantığı: Engelden Kaçma ----------

  if (mesafeDegeri < esikDegeri) {
    // Engel YOK / Uzak -> İLERİ
    Serial.println("Durum: Guvenli -> ILERI");
    ileri();
  } 
  else {
    // Engel VAR / YAKIN -> GERI + DON
    Serial.println("Durum: ENGEL YAKIN! -> Kacis Manevrasi");
    kacisManevrasi();
  }

  delay(10); // Döngü çok hızlı akmasın
}

// ----------------- Hareket Fonksiyonları -----------------

void ileri() {
  analogWrite(SOL_MOTOR1, 100);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 100);
  analogWrite(SAG_MOTOR2, 0);
}

void geri() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 100);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 100);
}

void sag() { // Yerinde saga don (pivot)
  analogWrite(SOL_MOTOR1, 100);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 100);
}

void sol() { // Yerinde sola don (pivot)
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 100);
  analogWrite(SAG_MOTOR1, 100);
  analogWrite(SAG_MOTOR2, 0);
}

void dur() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 0);
}

// ----------------- Kacis Manevrasi -----------------

void kacisManevrasi() {
  // 1. Biraz geri git
  geri();
  delay(300);   // 0.3 saniye geri

  // 2. Engelden uzaklasmak icin saga veya sola don
  // İstersen hep saga döndür:
  sag();
  delay(300);   // 0.3 saniye don

  // 3. Dur, loop tekrar ileri komutu verecek
  dur();
}
