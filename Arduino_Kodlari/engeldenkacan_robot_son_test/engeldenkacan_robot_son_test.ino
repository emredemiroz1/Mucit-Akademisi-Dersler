// Motor pinleri
#define SOL1 5
#define SOL2 6
#define SAG1 9
#define SAG2 10

// Sensör pinleri
#define SENSOR_SOL  A1
#define SENSOR_SAG  A0

int solDeger = 0;
int sagDeger = 0;

int esikDeger = 450;   // Engeli algılama eşiği

//------------------------------------------------------

void setup() {
  pinMode(SOL1, OUTPUT);
  pinMode(SOL2, OUTPUT);
  pinMode(SAG1, OUTPUT);
  pinMode(SAG2, OUTPUT);

  pinMode(SENSOR_SOL, INPUT);
  pinMode(SENSOR_SAG, INPUT);

  delay(2000); // başlama gecikmesi
}

//------------------------------------------------------

void loop() {

  // Sensör değerlerini oku
  solDeger = analogRead(SENSOR_SOL);
  sagDeger = analogRead(SENSOR_SAG);

  // ---------------- Hareket Kararları ----------------

  if (solDeger > esikDeger && sagDeger > esikDeger) {
    // Engel yok → ileri
    ileri();
  }

  else if (solDeger < esikDeger && sagDeger > esikDeger) {
    // Sol engel → geri + sağa
    geri();
    delay(300);
    sagaDon();
    delay(300);
    dur();
  }

  else if (solDeger > esikDeger && sagDeger < esikDeger) {
    // Sağ engel → geri + sola
    geri();
    delay(300);
    solaDon();
    delay(300);
    dur();
  }

  else {
    // İki sensör de engel gördü → geri + uzun sağa (180 dereceye yakın)
    geri();
    delay(400);
    sagaDon();
    delay(700);
    dur();
  }

  delay(20);
}

//------------------------------------------------------
// Motor fonksiyonları

void ileri() {
  analogWrite(SOL1, 150);
  analogWrite(SOL2, 0);
  analogWrite(SAG1, 150);
  analogWrite(SAG2, 0);
}

void geri() {
  analogWrite(SOL1, 0);
  analogWrite(SOL2, 150);
  analogWrite(SAG1, 0);
  analogWrite(SAG2, 150);
}

void sagaDon() {
  analogWrite(SOL1, 150);
  analogWrite(SOL2, 0);
  analogWrite(SAG1, 0);
  analogWrite(SAG2, 150);
}

void solaDon() {
  analogWrite(SOL1, 0);
  analogWrite(SOL2, 150);
  analogWrite(SAG1, 150);
  analogWrite(SAG2, 0);
}

void dur() {
  analogWrite(SOL1, 0);
  analogWrite(SOL2, 0);
  analogWrite(SAG1, 0);
  analogWrite(SAG2, 0);
}
