// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders 3: D4 varsayımdır. Yalnız sabit git/dur çıkışlı modül testi.
// Ham IR kumanda kodlarını çözmez.
// unsigned long: millis() saatini saklayan büyük tam sayı.
int led11 = 11;
int led12 = 12;
int led13 = 13;
int buzzer = 3;
int kumandaPini=4;
// Varsayilan, kabloyu dogrula.
bool oncekiDurum=false;
unsigned long degismeZamani=0,sonYazmaZamani=0,sesBaslamaZamani=0;
bool sesCaldi=false;
// setup: Kart açılınca yalnız bir kez çalışır.
void setup() {
  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led13, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
  // Motor çıkışları kapalı: bu derste yalnız kumandayı ölçüyoruz.
  pinMode(5, OUTPUT); digitalWrite(5, LOW);
  pinMode(6, OUTPUT); digitalWrite(6, LOW);
  pinMode(9, OUTPUT); digitalWrite(9, LOW);
  pinMode(10, OUTPUT); digitalWrite(10, LOW);
  pinMode(kumandaPini,INPUT);
}
// loop: Kart açık kaldıkça bu adımları tekrar tekrar yapar.
void loop() {
  
  // Motorlar kapalı kalır.
  unsigned long simdi=millis();
  bool birGeldi=digitalRead(kumandaPini)==HIGH;
  if(birGeldi!=oncekiDurum){
    oncekiDurum=birGeldi;
    degismeZamani=simdi;
    sesCaldi=false;
  }
  digitalWrite(led11,birGeldi);
  digitalWrite(led12,LOW);
  digitalWrite(led13,LOW);
  if(birGeldi && !sesCaldi && simdi-degismeZamani>=100){
    tone(buzzer,1600);
    sesBaslamaZamani=simdi;
    sesCaldi=true;
  }
  if(!birGeldi || (sesCaldi && simdi-sesBaslamaZamani>=150))noTone(buzzer);
  if(simdi-sonYazmaZamani>=100){
    sonYazmaZamani=simdi;
    Serial.print("D4=");
    Serial.println(birGeldi); // 1 veya 0 yazdırır.
  }
}
