// Ders 9 - Cizgide Duran Robot
// Sensor siyah cizgiyi algilayinca robot durur.

int cizgiSensoru = A0;
int esikDeger = 500;

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
  int sensorDegeri = analogRead(cizgiSensoru);

  if (sensorDegeri > esikDeger) {
    dur();
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

void dur() {
  digitalWrite(sagMotor1, LOW);
  digitalWrite(sagMotor2, LOW);
  digitalWrite(solMotor1, LOW);
  digitalWrite(solMotor2, LOW);
}

