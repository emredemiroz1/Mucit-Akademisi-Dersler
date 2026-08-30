// Ders 11 - Sag Duvar Takip
// Robot basit kararlarla sag duvari takip eder.

int onSensor = A0;
int sagSensor = A1;

int onEsik = 300;
int yakinEsik = 450;
int uzakEsik = 190;

int sagMotor1 = 5;
int sagMotor2 = 6;
int solMotor1 = 9;
int solMotor2 = 10;
int hiz = 160;

void setup() {
  pinMode(sagMotor1, OUTPUT);
  pinMode(sagMotor2, OUTPUT);
  pinMode(solMotor1, OUTPUT);
  pinMode(solMotor2, OUTPUT);
}

void loop() {
  int onDeger = analogRead(onSensor);
  int sagDeger = analogRead(sagSensor);

  if (onDeger > onEsik) {
    solaDon();
    delay(500);
  } else if (sagDeger > yakinEsik) {
    solaCek();
  } else if (sagDeger < uzakEsik) {
    sagaCek();
  } else {
    ileri();
  }
}

void ileri() {
  analogWrite(sagMotor1, hiz);
  digitalWrite(sagMotor2, LOW);
  analogWrite(solMotor1, hiz);
  digitalWrite(solMotor2, LOW);
}

void solaDon() {
  analogWrite(sagMotor1, hiz);
  digitalWrite(sagMotor2, LOW);
  digitalWrite(solMotor1, LOW);
  analogWrite(solMotor2, hiz);
}

void solaCek() {
  analogWrite(sagMotor1, hiz);
  digitalWrite(sagMotor2, LOW);
  analogWrite(solMotor1, 90);
  digitalWrite(solMotor2, LOW);
}

void sagaCek() {
  analogWrite(sagMotor1, 90);
  digitalWrite(sagMotor2, LOW);
  analogWrite(solMotor1, hiz);
  digitalWrite(solMotor2, LOW);
}
