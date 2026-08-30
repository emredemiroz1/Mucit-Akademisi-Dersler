// Ders 7 - Klavyeden LED Kontrol
// Seri ekrandan gelen harfe gore LED yakar.

int kirmiziLed = 11;
int sariLed = 12;
int yesilLed = 13;

void setup() {
  Serial.begin(9600);

  pinMode(kirmiziLed, OUTPUT);
  pinMode(sariLed, OUTPUT);
  pinMode(yesilLed, OUTPUT);

  Serial.println("r, y, g veya s harfi gonderin.");
}

void loop() {
  if (Serial.available() > 0) {
    char komut = Serial.read();

    digitalWrite(kirmiziLed, LOW);
    digitalWrite(sariLed, LOW);
    digitalWrite(yesilLed, LOW);

    if (komut == 'r') {
      digitalWrite(kirmiziLed, HIGH);
    } else if (komut == 'y') {
      digitalWrite(sariLed, HIGH);
    } else if (komut == 'g') {
      digitalWrite(yesilLed, HIGH);
    } else if (komut == 's') {
      Serial.println("Tum LED'ler kapandi.");
    }
  }
}

