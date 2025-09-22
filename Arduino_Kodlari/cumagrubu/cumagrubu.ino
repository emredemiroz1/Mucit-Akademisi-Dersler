 // Buzzer pinini buraya bağla (örnek D8)

void setup() {
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(A0);  // Potansiyometreyi oku
  Serial.println(potValue);

  if (potValue < 250) {        
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    
  } 
  else if (potValue < 500) {   
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    
  } 
  else if (potValue < 750) {   
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    
  } 
  else {                        
    // 750 ve üstü: tüm LED'ler yanacak ve buzzer ötecek
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    tone(3,500,100);
  }

  delay(100);
}
