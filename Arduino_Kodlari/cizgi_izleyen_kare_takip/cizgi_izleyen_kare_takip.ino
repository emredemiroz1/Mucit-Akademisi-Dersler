// ---------- Motor Pinleri (Önceki kodunuzla aynı) ----------
#define SOL_MOTOR1 5
#define SOL_MOTOR2 6
#define SAG_MOTOR1 9
#define SAG_MOTOR2 10

// ---------- Sensör Pinleri (2 Sensörlü Sumo Mantığı) ----------
#define SOL_SENSOR A0  // Sol ön sensör
#define SAG_SENSOR A7  // Sağ ön sensör

// Sensör Değerleri ve Eşik
int solSensor_value = 0;
int sagSensor_value = 0;
int esikDegeri = 850;   // 850 altı BEYAZ (zemin), üstü SİYAH (çizgi)

void setup() {
  // Motor pinlerini çıkış olarak ayarla
  pinMode(SOL_MOTOR1, OUTPUT);
  pinMode(SOL_MOTOR2, OUTPUT);
  pinMode(SAG_MOTOR1, OUTPUT);
  pinMode(SAG_MOTOR2, OUTPUT);

  // Sensör pinlerini giriş olarak ayarla (Aslında analog için gerekmez ama iyi bir alışkanlıktır)
  pinMode(SOL_SENSOR, INPUT);
  pinMode(SAG_SENSOR, INPUT);
  
  Serial.begin(9600);
  Serial.println("=== Sistem Basladi ===");
  Serial.println("Mod: Arena Icinde Kal (Sumo Mantigi)");
  Serial.print("Esik Degeri: ");
  Serial.println(esikDegeri);
  
  // Robota başlamak için 3 saniye bekleme süresi
  Serial.println("Baslamak icin 3 saniye...");
  delay(3000);
  Serial.println("BASLA!");
}

void loop() {
  // Her iki sensörden de değerleri oku
  solSensor_value = analogRead(SOL_SENSOR);
  sagSensor_value = analogRead(SAG_SENSOR);

  // Sensör değerlerini seri porta yazdır (hata ayıklama için)
  Serial.print("Sol: ");
  Serial.print(solSensor_value);
  Serial.print(" | Sag: ");
  Serial.println(sagSensor_value);

  // ---------- Hareket Mantığı: Arenadan Kaçınma ----------

  if (solSensor_value < esikDegeri && sagSensor_value < esikDegeri) {
    // 1. Durum: Her iki sensör de BEYAZ görüyor (Arenanın içindeyiz)
    // Görev: İlerle
    Serial.println("Durum: Zemin (Beyaz) -> ILERI");
    ileri();
  } 
  else if (solSensor_value > esikDegeri && sagSensor_value < esikDegeri) {
    // 2. Durum: Sol sensör SİYAH gördü (Sol kenara geldik)
    // Görev: Geri git ve SAĞA dön (çizgiden uzağa)
    Serial.println("Durum: SOL CIZGI! -> Geri ve Saga Don");
    kacirmaManvuerasi_Sag();
  }
  else if (solSensor_value < esikDegeri && sagSensor_value > esikDegeri) {
    // 3. Durum: Sağ sensör SİYAH gördü (Sağ kenara geldik)
    // Görev: Geri git ve SOLA dön (çizgiden uzağa)
    Serial.println("Durum: SAG CIZGI! -> Geri ve Sola Don");
    kacirmaManvuerasi_Sol();
  }
  else {
    // 4. Durum: Her iki sensör de SİYAH gördü (Tamamen çizgiye çıktık veya köşeye geldik)
    // Görev: Geri git ve daha keskin dön (örn: sağa)
    Serial.println("Durum: TAM CIZGI! -> Geri ve Keskin Saga Don");
    kacirmaManvuerasi_Sag(); // Aynı manevrayı kullanabilir veya daha uzun süre dönebiliriz
  }
  
  // Döngünün çok hızlı çalışıp seri portu kilitlememesi için küçük bir gecikme
  delay(10); 
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

void sag() { // Yerinde sağa döner (pivot)
  analogWrite(SOL_MOTOR1, 100);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 100);
}

void sol() { // Yerinde sola döner (pivot)
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

// ----------------- Özel Manevra Fonksiyonları -----------------

// Çizgiyi solda görünce yapılacak kaçış hareketi
void kacirmaManvuerasi_Sag() {
  // 1. Önce biraz geri git
  geri();
  delay(300); // 0.3 saniye geri git (robotun hızına göre ayarlayın)

  // 2. Çizgiden uzaklaşmak için SAĞA dön
  sag();
  delay(250); // 0.25 saniye dön (robotun hızına göre ayarlayın)
  
  // 3. Dur ve loop'un tekrar ileri gitmesini bekle
  dur();
}

// Çizgiyi sağda görünce yapılacak kaçış hareketi
void kacirmaManvuerasi_Sol() {
  // 1. Önce biraz geri git
  geri();
  delay(300); // 0.3 saniye geri git

  // 2. Çizgiden uzaklaşmak için SOLA dön
  sol();
  delay(250); // 0.25 saniye dön
  
  // 3. Dur ve loop'un tekrar ileri gitmesini bekle
  dur();
}