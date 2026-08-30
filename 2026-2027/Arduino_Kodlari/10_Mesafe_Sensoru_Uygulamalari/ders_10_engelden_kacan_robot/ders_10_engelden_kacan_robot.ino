// Ders 10 - Engelden Kacan Robot
// A0 pinindeki mesafe sensoru ile engel kontrolu yapar.

int mesafeSensoru = A0;
int engelEsigi = 300;

int sagMotor1 = 5;
int sagMotor2 = 6;
int solMotor1 = 9;
int solMotor2 = 10;
int hiz = 170;

void setup() {
  pinMode(sagMotor1, OUTPUT);
  pinMode(sagMotor2, OUTPUT);
  pinMode(solMotor1, OUTPUT);
  pinMode(solMotor2, OUTPUT);
}

void loop() {
  int mesafeDegeri = analogRead(mesafeSensoru);

  if (mesafeDegeri > engelEsigi) {
    sagaDon();
    delay(500);
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

void sagaDon() {
  digitalWrite(sagMotor1, LOW);
  analogWrite(sagMotor2, hiz);
  analogWrite(solMotor1, hiz);
  digitalWrite(solMotor2, LOW);
}

