// ---------- Motor Pinleri ----------
#define SOL_MOTOR1 5
#define SOL_MOTOR2 6
#define SAG_MOTOR1 9
#define SAG_MOTOR2 10

// ---------- Sensör Pinleri ----------
// Solda 2 sensör
#define SOL_SENSOR_IC   A1   // Sol iç sensör
#define SOL_SENSOR_DIS  A2   // Sol dış sensör

// Sağda 2 sensör
#define SAG_SENSOR_IC   A6   // Sağ iç sensör
#define SAG_SENSOR_DIS  A7   // Sağ dış sensör

// Sensörlerden gelen değerler
int solIcDeger  = 0;
int solDisDeger = 0;
int sagIcDeger  = 0;
int sagDisDeger = 0;

// Eşik değeri: BU DEĞERİN ÜSTÜ "SİYAH", ALTI "BEYAZ" OLSUN DİYE KULLANIYORUZ
int esikDegeri = 850;

void setup() {
  // Motor pinlerini çıkış yap
  pinMode(SOL_MOTOR1, OUTPUT);
  pinMode(SOL_MOTOR2, OUTPUT);
  pinMode(SAG_MOTOR1, OUTPUT);
  pinMode(SAG_MOTOR2, OUTPUT);

  // Sensör pinlerini giriş yap
  pinMode(SOL_SENSOR_IC,  INPUT);
  pinMode(SOL_SENSOR_DIS, INPUT);
  pinMode(SAG_SENSOR_IC,  INPUT);
  pinMode(SAG_SENSOR_DIS, INPUT);

  Serial.begin(9600);
  Serial.println("Robot Basladi!");
  delay(3000);  // 3 saniye bekle, sonra başlasın
}

void loop() {
  // ------ 1) Sensörleri oku ------
  solIcDeger  = analogRead(SOL_SENSOR_IC);
  solDisDeger = analogRead(SOL_SENSOR_DIS);
  sagIcDeger  = analogRead(SAG_SENSOR_IC);
  sagDisDeger = analogRead(SAG_SENSOR_DIS);

  // İstersen seri ekrandan gör
  Serial.print("SolIc: ");  Serial.print(solIcDeger);
  Serial.print("  SolDis: "); Serial.print(solDisDeger);
  Serial.print("  SagIc: ");  Serial.print(sagIcDeger);
  Serial.print("  SagDis: "); Serial.println(sagDisDeger);

  // ------ 2) Sensörlere göre DURUM BELİRLE ------

  // Solda çizgi var mı? (Herhangi biri siyah ise)
  bool soldaCizgiVar = (solIcDeger > esikDegeri) || (solDisDeger > esikDegeri);

  // Sağda çizgi var mı? (Herhangi biri siyah ise)
  bool sagdaCizgiVar = (sagIcDeger > esikDegeri) || (sagDisDeger > esikDegeri);

  // Hepsi beyaz mı?
  bool hepsiBeyaz =
    (solIcDeger  < esikDegeri) &&
    (solDisDeger < esikDegeri) &&
    (sagIcDeger  < esikDegeri) &&
    (sagDisDeger < esikDegeri);

  // ------ 3) Karar Ver ve Hareket Et ------

  if (hepsiBeyaz) {
    // Hepsi BEYAZ → İLERİ
    ileri();
  }
  else if (soldaCizgiVar && !sagdaCizgiVar) {
    // Sadece solda çizgi → Geri + SAĞA dön
    geri();
    delay(300);
    sagaDon();
    delay(250);
    dur();
  }
  else if (sagdaCizgiVar && !soldaCizgiVar) {
    // Sadece sağda çizgi → Geri + SOLA dön
    geri();
    delay(300);
    solaDon();
    delay(250);
    dur();
  }
  else {
    // Hem solda hem sağda çizgi → köşe gibi durum
    // Geri + SAĞA dön
    geri();
    delay(300);
    sagaDon();
    delay(300);
    dur();
  }

  delay(10); // Döngüyü biraz yavaşlat
}

// ----------------- Hareket Fonksiyonları -----------------

// İleri git
void ileri() {
  // Hızı istersen düşürebilirsin (0-255 arası)
  analogWrite(SOL_MOTOR1, 100);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 100);
  analogWrite(SAG_MOTOR2, 0);
}

// Geri git
void geri() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 100);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 100);
}

// Yerinde SAĞA dön
void sagaDon() {
  analogWrite(SOL_MOTOR1, 100);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 100);
}

// Yerinde SOLA dön
void solaDon() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 100);
  analogWrite(SAG_MOTOR1, 100);
  analogWrite(SAG_MOTOR2, 0);
}

// Dur
void dur() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 0);
}
