// Ders 12 - Mini Sumo Baslangic
// Robot 5 saniye bekler, sonra basit sumo davranisi yapar.

int solRakipSensoru = A0;
int sagRakipSensoru = A1;
int cizgiSensoru = A2;

int rakipEsigi = 400;
int cizgiEsigi = 700;

int sagMotor1 = 5;
int sagMotor2 = 6;
int solMotor1 = 9;
int solMotor2 = 10;
int hiz = 200;

void setup() {
  pinMode(sagMotor1, OUTPUT);
  pinMode(sagMotor2, OUTPUT);
  pinMode(solMotor1, OUTPUT);
  pinMode(solMotor2, OUTPUT);

  delay(5000);
}

void loop() {
  int solRakip = analogRead(solRakipSensoru);
  int sagRakip = analogRead(sagRakipSensoru);
  int cizgi = analogRead(cizgiSensoru);

  if (cizgi > cizgiEsigi) {
    geri();
    delay(400);
    sagaDon();
    delay(300);
  } else if (solRakip > rakipEsigi && sagRakip > rakipEsigi) {
    ileri();
  } else if (solRakip > rakipEsigi) {
    solaDon();
  } else if (sagRakip > rakipEsigi) {
    sagaDon();
  } else {
    ara();
  }
}

void ileri() {
  analogWrite(sagMotor1, hiz);
  digitalWrite(sagMotor2, LOW);
  analogWrite(solMotor1, hiz);
  digitalWrite(solMotor2, LOW);
}

void geri() {
  digitalWrite(sagMotor1, LOW);
  analogWrite(sagMotor2, hiz);
  digitalWrite(solMotor1, LOW);
  analogWrite(solMotor2, hiz);
}

void sagaDon() {
  digitalWrite(sagMotor1, LOW);
  analogWrite(sagMotor2, hiz);
  analogWrite(solMotor1, hiz);
  digitalWrite(solMotor2, LOW);
}

void solaDon() {
  analogWrite(sagMotor1, hiz);
  digitalWrite(sagMotor2, LOW);
  digitalWrite(solMotor1, LOW);
  analogWrite(solMotor2, hiz);
}

void ara() {
  sagaDon();
  delay(100);
}
