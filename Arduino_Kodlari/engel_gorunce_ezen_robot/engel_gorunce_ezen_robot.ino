// ================= MOTOR PINLERI =================
#define SOL1 5
#define SOL2 6
#define SAG1 9
#define SAG2 10

// ================= SENSOR PINLERI =================
#define SENSOR_SOL  A0
#define SENSOR_SAG  A1

// ================= DEGISKENLER =================
int solDeger = 0;
int sagDeger = 0;

int esikDeger = 600;   // Engel algılama sınırı

// TEK HIZ SEVIYESI (arama + saldırı aynı)
int solHiz = 145;     // deneme ile ayarlanır
int sagHiz = 160;     // genelde biri biraz büyük olur

// =================================================

void setup() {
  pinMode(SOL1, OUTPUT);
  pinMode(SOL2, OUTPUT);
  pinMode(SAG1, OUTPUT);
  pinMode(SAG2, OUTPUT);

  pinMode(SENSOR_SOL, INPUT);
  pinMode(SENSOR_SAG, INPUT);

  delay(2000);
}

// =================================================

void loop() {

  solDeger = analogRead(SENSOR_SOL);
  sagDeger = analogRead(SENSOR_SAG);

  if (solDeger < esikDeger && sagDeger < esikDeger) {
    // Hedef yok → yavaşça sağa tarayarak ara
    
  }
  else if (solDeger > esikDeger && sagDeger > esikDeger) {
    // Hedef önde → ileri git
    delay(200);
    dur();
    ileri();
  }
  else if (solDeger > esikDeger) {
    // Hedef solda
    dur();
    solaDon();
  
  }
  else if (sagDeger > esikDeger) {
    // Hedef sağda
    dur();
    sagaDon();
  }
}

// =================================================
// HEDEF ARAMA (AYNI HIZ, SADECE FARKLI)

void hedefAra() {
  // Sol motor biraz hızlı → sağa doğru tarama
  analogWrite(SOL1, solHiz);
  analogWrite(SOL2, 0);

  analogWrite(SAG1, sagHiz);
  analogWrite(SAG2, 0);
}

// =================================================
// DUZ GITME

void ileri() {
  analogWrite(SOL1, solHiz);
  analogWrite(SOL2, 0);

  analogWrite(SAG1, sagHiz);
  analogWrite(SAG2, 0);
}

// =================================================
// DONUSLER

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