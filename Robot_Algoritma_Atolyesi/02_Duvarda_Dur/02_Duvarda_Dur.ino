// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders: 02_Duvarda_Dur
// int: tam sayı, bool: doğru/yanlış, float: ondalıklı sayı.
// millis(): kart açıldığından beri geçen milisaniye.
// Zamanlar int içine sığmaz; bu yüzden zaman için unsigned long kullanılır.
// Uzun delay yerine saati kontrol ediyoruz; kumandanın dur komutunu kaçırmayalım.
int solMotorIleri = 5; // Sol motorun ileri girişi.
int solMotorGeri = 6; // Sol motorun geri girişi.
int sagMotorIleri = 9; // Sağ motorun ileri girişi.
int sagMotorGeri = 10; // Sağ motorun geri girişi.
int taktikButonu = 7; // Basarak taktik sayısını değiştiririz.
int yonAnahtari = 2; // 0 sol, 1 sağ yönü seçer.
int led11 = 11; // 1 değerli lamba.
int led12 = 12; // 2 değerli lamba.
int led13 = 13; // 4 değerli lamba.
int buzzer = 3; // Ses çıkaran parça.
bool oncekiButon = false;
unsigned long butonDegismeZamani=0;
bool hamButon=false;
int hiziSinirla(int deger){
  return constrain(deger,-180,180);
}
void motorlariSur(int sol,int sag){
  sol=hiziSinirla(sol);
  sag=hiziSinirla(sag);
  // Once iki yonu kapat: yon degisiminde eski PWM acik kalmasin.
  analogWrite(solMotorIleri,0);
  analogWrite(solMotorGeri,0);
  analogWrite(sagMotorIleri,0);
  analogWrite(sagMotorGeri,0);
  if (sol >= 0) {
    analogWrite(solMotorIleri, sol);
  }
  else {
    analogWrite(solMotorGeri, -sol);
  }
  if (sag >= 0) {
    analogWrite(sagMotorIleri, sag);
  }
  else {
    analogWrite(sagMotorGeri, -sag);
  }
}
void pinleriHazirla(){
  pinMode(solMotorIleri, OUTPUT);
  pinMode(solMotorGeri, OUTPUT);
  pinMode(sagMotorIleri, OUTPUT);
  pinMode(sagMotorGeri, OUTPUT);
  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led13, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(taktikButonu,INPUT_PULLUP);
  pinMode(yonAnahtari,INPUT_PULLUP);
  Serial.begin(115200);
  motorlariSur(0,0);
}
bool butonaYeniBasildi(){
  unsigned long simdi=millis();
  bool basili=digitalRead(taktikButonu)==LOW;
  if(basili!=hamButon){
    hamButon=basili;
    butonDegismeZamani=simdi;
  }
  // Son değişimden beri 30 ms geçmediyse henüz basış sayma.
  if (simdi - butonDegismeZamani < 30) {
    return false;
  }
  // Yalnız yeni basışta true döndür; basılı tutmak sayıyı artırmasın.
  bool yeniBasis = basili && oncekiButon == false;
  oncekiButon=basili;
  return yeniBasis;
}
int kumandaPini=4;
// VARSAYIM: kart uzerinde dogrula.
// Yalniz cozulmus, surekli HIGH=git / LOW=dur cikisli MODUL icin.
// Ham IR alicisinin darbelerini bu kodla baslatma komutu saymayin!
bool kumandaTestiTamam=false;
// D4 testi tamamlaninca true.
bool durKomutuGoruldu=false;
unsigned long gitBaslamaZamani=0;
bool onceGitVardi=false;
bool kumandaGitDiyor(){
  bool birGeldi=digitalRead(kumandaPini)==HIGH;
  if(!birGeldi){
    durKomutuGoruldu=true;
    onceGitVardi=false;
    return false;
  }
  if(!onceGitVardi){
    onceGitVardi=true;
    gitBaslamaZamani=millis();
  }
  return kumandaTestiTamam && durKomutuGoruldu && millis()-gitBaslamaZamani>=100;
}
void kumandayiHazirla(){
  pinMode(kumandaPini,INPUT);
}
bool sensorTestiTamam=false;
// Esik degerlerini olcmeden acma.
int solEsik=400,sagEsik=400;
bool duvardaDurdu=false;
unsigned long sesBaslamaZamani=0;
// setup: Kart açılınca yalnız bir kez çalışır.
void setup() {
  pinleriHazirla();
  kumandayiHazirla();
}
// loop: Kart açık kaldıkça bu adımları tekrar tekrar yapar.
void loop() {
  if(!kumandaGitDiyor() || !sensorTestiTamam){
    motorlariSur(0,0);
    noTone(buzzer);
    if(digitalRead(kumandaPini)==LOW){
      duvardaDurdu=false;
      digitalWrite(led11,LOW);
      digitalWrite(led12,LOW);
      digitalWrite(led13,LOW);
    }
    return;
  }
  if(!duvardaDurdu && (analogRead(A0)>=solEsik || analogRead(A1)>=sagEsik)){
    duvardaDurdu=true;
    motorlariSur(0,0);
    digitalWrite(led11,HIGH);
    digitalWrite(led12,HIGH);
    digitalWrite(led13,HIGH);
    tone(buzzer,1600);
    sesBaslamaZamani=millis();
  }
  if(duvardaDurdu){
    motorlariSur(0,0);
    if(millis()-sesBaslamaZamani>=1000)noTone(buzzer);
  }
  else motorlariSur(70,70);
}
