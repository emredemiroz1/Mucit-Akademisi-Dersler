// Mucit Akademisi Tekrar Notları
// Bu kodun amacı: Potansiyometreyi çevirince 11,12,13 LED'leri ve buzzer ile 7 nota çalmaktır.

void setup() {
  pinMode(11, OUTPUT); // LED1
  pinMode(12, OUTPUT); // LED2
  pinMode(13, OUTPUT); // LED3
  pinMode(3, OUTPUT);  // Buzzer
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(A0);  // Potansiyometreyi oku (0-1023)
  Serial.println(potValue);

  if (potValue < 146) {           // 0-145 → DO
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    tone(3, 262, 100);            // DO
  } 
  else if (potValue < 292) {      // 146-291 → RE
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    tone(3, 294, 100);            // RE
  } 
  else if (potValue < 438) {      // 292-437 → MI
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    tone(3, 330, 100);            // MI
  } 
  else if (potValue < 584) {      // 438-583 → FA
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    tone(3, 349, 100);            // FA
  } 
  else if (potValue < 730) {      // 584-729 → SOL
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    tone(3, 392, 100);            // SOL
  } 
  else if (potValue < 876) {      // 730-875 → LA
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    tone(3, 440, 100);            // LA
  } 
  else {                          // 876-1023 → SI
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    tone(3, 494, 100);            // SI
  }

  delay(100); // küçük bekleme
}
