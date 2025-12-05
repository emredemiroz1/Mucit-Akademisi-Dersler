// Motor pinleri
#define SOL1 5
#define SOL2 6
#define SAG1 9
#define SAG2 10

// Sensör pinleri
#define SENSOR_SOL  A0
#define SENSOR_SAG  A1

int solDeger = 0;
int sagDeger = 0;

int esikDeger = 600;   // Engeli algılama eşiği
int motorHiz  = 150;   // Saldırı hızı (0-255)

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

  // ----- Mini Sumo Hareket Kararları -----

  if (solDeger < esikDeger && sagDeger < esikDeger) {
    // Hiç engel yok → Rakip aramak için sağa doğru dön
    sagaDon();
  }

  else if (solDeger > esikDeger && sagDeger > esikDeger) {
    // İki sensör de engel gördü → Rakip tam önde → İleri saldır
    ileri();
  }

  else if (solDeger > esikDeger && sagDeger < esikDeger) {
    // Sadece solda engel var → Sola dön, rakibe yönel
    solaDon();
  }

  else if (solDeger < esikDeger && sagDeger > esikDeger) {
    // Sadece sağda engel var → Sağa dön, rakibe yönel
    sagaDon();
  }

  delay(30);
}

//------------------------------------------------------
// Motor fonksiyonları

void ileri() {
  analogWrite(SOL1, motorHiz);
  analogWrite(SOL2, 0);
  analogWrite(SAG1, motorHiz);
  analogWrite(SAG2, 0);
}

void geri() {
  analogWrite(SOL1, 0);
  analogWrite(SOL2, motorHiz);
  analogWrite(SAG1, 0);
  analogWrite(SAG2, motorHiz);
}

void sagaDon() { // sağa kendi etrafında dön
  analogWrite(SOL1, motorHiz);
  analogWrite(SOL2, 0);
  analogWrite(SAG1, 0);
  analogWrite(SAG2, motorHiz);
}

void solaDon() { // sola kendi etrafında dön
  analogWrite(SOL1, 0);
  analogWrite(SOL2, motorHiz);
  analogWrite(SAG1, motorHiz);
  analogWrite(SAG2, 0);
}

void dur() {
  analogWrite(SOL1, 0);
  analogWrite(SOL2, 0);
  analogWrite(SAG1, 0);
  analogWrite(SAG2, 0);
}
