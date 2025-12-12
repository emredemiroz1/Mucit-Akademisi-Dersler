// ================= MOTOR PINLERI =================
#define SOL1 5
#define SOL2 6
#define SAG1 9
#define SAG2 10

// ================= SENSOR PINLERI =================
#define SENSOR_SOL  A0
#define SENSOR_SAG  A1

// ================= AYARLAR =================
int esikDeger = 600;

int solHiz = 145;
int sagHiz = 160;
// ===========================================

void setup() {
  pinMode(SOL1, OUTPUT);
  pinMode(SOL2, OUTPUT);
  pinMode(SAG1, OUTPUT);
  pinMode(SAG2, OUTPUT);

  pinMode(SENSOR_SOL, INPUT);
  pinMode(SENSOR_SAG, INPUT);

  delay(2000);
}

void loop() {
  int solDeger = analogRead(SENSOR_SOL);
  int sagDeger = analogRead(SENSOR_SAG);

  // SADECE SAĞDA ENGEL
  if (sagDeger > esikDeger && solDeger < esikDeger) {
    sagaDon();
  }

  // SADECE SOLDA ENGEL
  else if (solDeger > esikDeger && sagDeger < esikDeger) {
    solaDon();
  }

  // İKİ TARAFTA DA ENGEL
  else if (solDeger > esikDeger && sagDeger > esikDeger) {
    ileri();
  }

  // HİÇ ENGEL YOK
  else {
    dur();
  }

  delay(10);
}

// ================= FONKSIYONLAR =================

void ileri() {
  analogWrite(SOL1, solHiz);
  analogWrite(SOL2, 0);

  analogWrite(SAG1, sagHiz);
  analogWrite(SAG2, 0);
}

void sagaDon() {
  analogWrite(SOL1, solHiz);
  analogWrite(SOL2, 0);

  analogWrite(SAG1, 0);
  analogWrite(SAG2, sagHiz);
}

void solaDon() {
  analogWrite(SOL1, 0);
  analogWrite(SOL2, solHiz);

  analogWrite(SAG1, sagHiz);
  analogWrite(SAG2, 0);
}

void dur() {
  analogWrite(SOL1, 0);
  analogWrite(SOL2, 0);

  analogWrite(SAG1, 0);
  analogWrite(SAG2, 0);
}
