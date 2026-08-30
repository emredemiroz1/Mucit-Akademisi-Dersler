#define MESAFE_SENSOR A0   // A0'a bağlı sensör

int sensorDegeri = 0;

void setup() {
  Serial.begin(9600);
  pinMode(MESAFE_SENSOR, INPUT);
}

void loop() {
  sensorDegeri = analogRead(MESAFE_SENSOR);  // Sensör değerini oku

  Serial.print("Mesafe Sensor Degeri: ");
  Serial.println(sensorDegeri);              // Ekrana yazdır

  delay(100);
}
