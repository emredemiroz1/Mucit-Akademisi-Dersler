// Ders 13 - Bluetooth Robot Kontrol
// Seri haberlesmeden gelen komuta gore robot hareket eder.

int sagMotor1 = 5;
int sagMotor2 = 6;
int solMotor1 = 9;
int solMotor2 = 10;
int hiz = 180;

void setup() {
  Serial.begin(9600);

  pinMode(sagMotor1, OUTPUT);
  pinMode(sagMotor2, OUTPUT);
  pinMode(solMotor1, OUTPUT);
  pinMode(solMotor2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char komut = Serial.read();

    if (komut == 'F') {
      ileri();
    } else if (komut == 'B') {
      geri();
    } else if (komut == 'L') {
      solaDon();
    } else if (komut == 'R') {
      sagaDon();
    } else if (komut == 'S') {
      dur();
    }
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

void dur() {
  digitalWrite(sagMotor1, LOW);
  digitalWrite(sagMotor2, LOW);
  digitalWrite(solMotor1, LOW);
  digitalWrite(solMotor2, LOW);
}
