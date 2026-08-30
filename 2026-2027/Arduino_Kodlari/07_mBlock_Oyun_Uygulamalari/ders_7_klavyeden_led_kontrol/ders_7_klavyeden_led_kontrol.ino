// Ders 7 - Klavyeden LED Kontrol
// Seri ekrandan gelen harfe gore LED yakar.
// ROBOMER kartta LED'ler 11, 12 ve 13 numarali pinlerdedir.

int led11 = 11;
int led12 = 12;
int led13 = 13;

void setup() {
  Serial.begin(9600);

  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led13, OUTPUT);

  Serial.println("r, y, g veya s harfi gonderin.");
}

void loop() {
  if (Serial.available() > 0) {
    char komut = Serial.read();

    digitalWrite(led11, LOW);
    digitalWrite(led12, LOW);
    digitalWrite(led13, LOW);

    if (komut == 'r') {
      digitalWrite(led11, HIGH);
    } else if (komut == 'y') {
      digitalWrite(led12, HIGH);
    } else if (komut == 'g') {
      digitalWrite(led13, HIGH);
    } else if (komut == 's') {
      Serial.println("Tum LED'ler kapandi.");
    }
  }
}
