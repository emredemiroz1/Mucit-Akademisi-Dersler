// Motor pinlerini tanımlıyoruz
#define SOL_MOTOR1 5   
#define SOL_MOTOR2 6   
#define SAG_MOTOR1 9   
#define SAG_MOTOR2 10 

char komut; // Telefon'dan gelen komut

void setup() {
  // Motor pinlerini çıkış olarak ayarlıyoruz
  pinMode(SOL_MOTOR1, OUTPUT);
  pinMode(SOL_MOTOR2, OUTPUT);
  pinMode(SAG_MOTOR1, OUTPUT);
  pinMode(SAG_MOTOR2, OUTPUT);

  // Seri haberleşme (Hem Bluetooth hem USB Serial aynı hattan gelir)
  Serial.begin(9600);   
  Serial.println("Bluetooth araba hazır. Komut bekleniyor...");
}

void loop() {
  if (Serial.available()) {      // Bluetooth'tan veri geldiyse
    komut = Serial.read();       // Karakteri oku
    Serial.println(komut);       // Seri monitöre yaz

    // Gelen komuta göre hareket et
    if (komut == 'F') ileri();    // Forward
    else if (komut == 'B') geri(); // Backward
    else if (komut == 'R') sag();  // Right
    else if (komut == 'L') sol();  // Left
    else if (komut == 'S') dur();  // Stop
  }
}

// ----------------- Fonksiyonlar -----------------

void ileri() {
  analogWrite(SOL_MOTOR1, 150);   
  analogWrite(SOL_MOTOR2, 0);

  analogWrite(SAG_MOTOR1, 150);   
  analogWrite(SAG_MOTOR2, 0);
}

void geri() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 150);   

  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 150);   
}

void sag() {
  analogWrite(SOL_MOTOR1, 150);   
  analogWrite(SOL_MOTOR2, 0);

  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 150);   
}

void sol() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 150);   

  analogWrite(SAG_MOTOR1, 150);   
  analogWrite(SAG_MOTOR2, 0);
}

void dur() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 0);
}
