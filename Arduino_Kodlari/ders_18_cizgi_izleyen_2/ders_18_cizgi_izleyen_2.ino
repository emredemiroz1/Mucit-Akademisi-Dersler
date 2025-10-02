#define SOL_MOTOR1 5
#define SOL_MOTOR2 6
#define SAG_MOTOR1 9
#define SAG_MOTOR2 10

#define SOL_SENSOR A0     // Sol sensör
#define SAG_SENSOR A7     // Sağ sensör
int solDeger, sagDeger;
int esikDeger = 250;

// ---------------- MOTOR HAREKETLERİ ----------------
void ileri() {
  analogWrite(SOL_MOTOR1, 150);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 150);
  analogWrite(SAG_MOTOR2, 0);
}

void saga() {
  analogWrite(SOL_MOTOR1, 150);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 0);
}

void sola() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 150);
  analogWrite(SAG_MOTOR2, 0);
}

void dur() {
  analogWrite(SOL_MOTOR1, 0);
  analogWrite(SOL_MOTOR2, 0);
  analogWrite(SAG_MOTOR1, 0);
  analogWrite(SAG_MOTOR2, 0);
}
// ---------------------------------------------------

void setup() {
  pinMode(SOL_MOTOR1, OUTPUT);
  pinMode(SOL_MOTOR2, OUTPUT);
  pinMode(SAG_MOTOR1, OUTPUT);
  pinMode(SAG_MOTOR2, OUTPUT);

  pinMode(SOL_SENSOR, INPUT);
  pinMode(SAG_SENSOR, INPUT);

  Serial.begin(9600);
}

void loop() {
  solDeger = analogRead(SOL_SENSOR);
  sagDeger = analogRead(SAG_SENSOR);

  Serial.print("Sol: "); Serial.print(solDeger);
  Serial.print("  Sag: "); Serial.println(sagDeger);

  // Karar tablosu
  if (solDeger < esikDeger && sagDeger < esikDeger) {
    ileri();         // İkisi de beyaz → ileri
  } 
  else if (solDeger > esikDeger && sagDeger < esikDeger) {
    saga();          // Sol siyah → sağa
  } 
  else if (solDeger < esikDeger && sagDeger > esikDeger) {
    sola();          // Sağ siyah → sola
  } 
  else {
    dur();           // İkisi siyah → dur
  }
}
