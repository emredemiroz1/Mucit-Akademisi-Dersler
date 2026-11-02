// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders 2: Sharp sensörlerini ölçelim. Seri Monitör: 115200.
// Sensör modeli: GP2Y0A21, nominal aralık 10–80 cm.
int solSensor = A0;
int sagSensor = A1;
int solDeger = 0;
int sagDeger = 0;

void setup() {
  Serial.begin(115200); // Bilgisayarla yazışmayı başlat.
  // Bu derste motorları çalıştırmıyoruz.
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}

void loop() {
  solDeger = analogRead(solSensor); // 0 ile 1023 arasında ham ölçüm.
  sagDeger = analogRead(sagSensor);
  Serial.print("Sol sensor: ");
  Serial.print(solDeger);
  Serial.print("   Sag sensor: ");
  Serial.println(sagDeger); // println yazınca yeni satıra geçer.
  delay(100); // Motorlar kapalı; okumayı kolaylaştırmak için bekleyebiliriz.
  // Hedefi 80, 60, 40, 20, 10 cm'ye koy ve değerleri defterine yaz.
  // Bunlar santimetre değil! 10 cm altında ölçüm yanıltıcı olabilir.
}
