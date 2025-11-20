// ---------- Motor Pinleri ----------
#define SOL_MOTOR1 6
#define SOL_MOTOR2 5
#define SAG_MOTOR1 9
#define SAG_MOTOR2 10

// ---------- Sensör Pinleri ----------
#define SOL_SENSOR1 A0  // Sol iç sensör
#define SOL_SENSOR2 A1  // Sol dış sensör
#define SAG_SENSOR1 A6  // Sağ iç sensör
#define SAG_SENSOR2 A7  // Sağ dış sensör

// Sensör Değerleri ve Eşik
int solSensor1_value = 0;
int solSensor2_value = 0;
int sagSensor1_value = 0;
int sagSensor2_value = 0;

// Bunu SAHADA ayarla (başlangıç için 700 deneyebiliriz)
int esikDegeri = 700;   // altında/beyaz - üstünde/siyah (sensörüne göre ters de olabilir!)

void setup() {
  pinMode(SOL_MOTOR1, OUTPUT);
  pinMode(SOL_MOTOR2, OUTPUT);
  pinMode(SAG_MOTOR1, OUTPUT);
  pinMode(SAG_MOTOR2, OUTPUT);

  pinMode(SOL_SENSOR1, INPUT);
  pinMode(SOL_SENSOR2, INPUT);
  pinMode(SAG_SENSOR1, INPUT);
  pinMode(SAG_SENSOR2, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Sensörleri oku
  okuSensorler();

  // DEBUG: İstersen seri ekrandan bak
  Serial.print("L1: "); Serial.print(solSensor1_value);
  Serial.print("  L2: "); Serial.print(solSensor2_value);
  Serial.print("  R1: "); Serial.print(sagSensor1_value);
  Serial.print("  R2: "); Serial.println(sagSensor2_value);

  // 1) SOL iki sensör siyah → hafif SAĞA dön + İLERİ
  if (solSensor1_value > esikDegeri &&
      solSensor2_value > esikDegeri &&
      sagSensor1_value < esikDegeri &&
      sagSensor2_value < esikDegeri)
  {
    // Hemen dönmesin → biraz bekle, tekrar kontrol et
    delay(60);
    okuSensorler();

    if (solSensor1_value > esikDegeri &&
        solSensor2_value > esikDegeri &&
        sagSensor1_value < esikDegeri &&
        sagSensor2_value < esikDegeri)
    {
      // İstersen önce biraz yavaşla/dur
      dur();
      delay(40);

      sagHafif();
      delay(150);   // çok uzun olmasın
      ileri();
    }
  }
  // 2) SAĞ iki sensör siyah → hafif SOLA dön + İLERİ
  else if (sagSensor1_value > esikDegeri &&
           sagSensor2_value > esikDegeri &&
           solSensor1_value < esikDegeri &&
           solSensor2_value < esikDegeri)
  {
    // Hemen dönmesin → biraz bekle, tekrar kontrol et
    delay(60);
    okuSensorler();

    if (sagSensor1_value > esikDegeri &&
        sagSensor2_value > esikDegeri &&
        solSensor1_value < esikDegeri &&
        solSensor2_value < esikDegeri)
    {
      dur();
      delay(40);

      solHafif();
      delay(150);
      ileri();
    }
  }
  // 3) Diğer tüm durumlarda → yavaş İLERİ
  else {
    ileri();     // istersen burayı dur(); yapabilirsin
  }

  delay(20);
}

// ----------------- Sensör Okuma Fonksiyonu -----------------
void okuSensorler() {
  solSensor1_value = analogRead(SOL_SENSOR1);
  solSensor2_value = analogRead(SOL_SENSOR2);
  sagSensor1_value = analogRead(SAG_SENSOR1);
  sagSensor2_value = analogRead(SAG_SENSOR2);
}

// ----------------- Hareket Fonksiyonları -----------------

void ileri() {
  // HIZ DÜŞÜRÜLDÜ
  analogWrite(SOL_MOTOR1, 70);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 70);
  analogWrite(SAG_MOTOR2, 0);
}

void geri() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 70);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 70);
}

void sag() { // Yerinde sağa dön (pivot)
  analogWrite(SOL_MOTOR1, 70);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 70);
}

void sol() { // Yerinde sola dön (pivot)
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 70);
  analogWrite(SAG_MOTOR1, 70);
  analogWrite(SAG_MOTOR2, 0);
}

void dur() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 0);
}

// ----------------- Hafif Dönüşler -----------------

// Sol iki sensör siyah → hafif sağ kırmak için
void sagHafif() {
  // Sol teker biraz daha hızlı, sağ teker biraz daha yavaş
  analogWrite(SOL_MOTOR1, 80);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 50);
  analogWrite(SAG_MOTOR2, 0);
}

// Sağ iki sensör siyah → hafif sol kırmak için
void solHafif() {
  // Sağ teker biraz daha hızlı, sol teker biraz daha yavaş
  analogWrite(SOL_MOTOR1, 50);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 80);
  analogWrite(SAG_MOTOR2, 0);
}
