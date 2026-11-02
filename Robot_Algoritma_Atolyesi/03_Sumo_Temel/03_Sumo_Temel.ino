// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders: 03_Sumo_Temel
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
// D11=1, D12=2, D13=4. D2 LOW=sol, HIGH=sag.
int taktikNo=0;
void taktigiGoster(){
  // led11: 1 değerli lamba.
  if (taktikNo == 1 || taktikNo == 3 || taktikNo == 5 || taktikNo == 7) {
    digitalWrite(led11, HIGH);
  }
  else {
    digitalWrite(led11, LOW);
  }
  // led12: 2 değerli lamba.
  if (taktikNo == 2 || taktikNo == 3 || taktikNo == 6 || taktikNo == 7) {
    digitalWrite(led12, HIGH);
  }
  else {
    digitalWrite(led12, LOW);
  }
  // led13: 4 değerli lamba.
  if (taktikNo == 4 || taktikNo == 5 || taktikNo == 6 || taktikNo == 7) {
    digitalWrite(led13, HIGH);
  }
  else {
    digitalWrite(led13, LOW);
  }
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
// MIDI SUMO: sadece A0/A1 Sharp, kenar sensoru YOK.
bool pidKullan=false;
bool sensorTestiTamam=false;
// Kalibrasyonu tamamla, sonra true yap.
int solEsik=400,sagEsik=400;
int solUzakDeger=100,solYakinDeger=700,sagUzakDeger=100,sagYakinDeger=700;
// 8 egitim taktigi: ilk dordunde sabit arama, son dordunde yon degisimi.
int ileriHizlari[8]={65,75,85,95,65,75,85,95};
int aramaHizlari[8]={35,40,45,50,35,40,45,50};
unsigned long sonOlcumZamani=0,sonGormeZamani=0,baslamaZamani=0;
bool calisiyor=false,aramaSuresiBitti=false,sagaAra=true;
int secilenTaktik=0;
float yakinligiHesapla(int deger,int farV,int nearV){
  if(nearV<=farV)return 0;
  return constrain(float(deger-farV)/(nearV-farV),0.0f,1.0f);
}
// setup: Kart açılınca yalnız bir kez çalışır.
void setup() {
  pinleriHazirla();
  kumandayiHazirla();
  taktigiGoster();
}
// loop: Kart açık kaldıkça bu adımları tekrar tekrar yapar.
void loop() {
  unsigned long simdi=millis();
  bool yeniBasis=butonaYeniBasildi();
  bool gitKomutu=kumandaGitDiyor();
  if(!gitKomutu || !sensorTestiTamam){
    motorlariSur(0,0);
    calisiyor=false;
    if(digitalRead(kumandaPini)==LOW){
      aramaSuresiBitti=false;
      if(yeniBasis){
        taktikNo = taktikNo + 1;
        if (taktikNo > 7) {
          taktikNo = 0;
        }
        taktigiGoster();
      }
    }
    return;
  }
  if(aramaSuresiBitti){
    motorlariSur(0,0);
    return;
  }
  if(!calisiyor){
    calisiyor=true;
    secilenTaktik=taktikNo;
    sagaAra=digitalRead(yonAnahtari)==HIGH;
    sonGormeZamani=baslamaZamani=simdi;
    sonOlcumZamani=simdi;
  }
  if(simdi-sonOlcumZamani<50)return;
  sonOlcumZamani=simdi;
  int solOlcum=analogRead(A0),sagOlcum=analogRead(A1);
  bool sol=solOlcum>=solEsik,sag=sagOlcum>=sagEsik;
  if(!sol&&!sag){
    if(simdi-sonGormeZamani>=15000){
      aramaSuresiBitti=true;
      motorlariSur(0,0);
      return;
    }
    bool saatYonunde=sagaAra;
    if(secilenTaktik>=4 && ((simdi-baslamaZamani)/1500)%2)saatYonunde=!saatYonunde;
    int aramaHizi=aramaHizlari[secilenTaktik];
    motorlariSur(saatYonunde?aramaHizi:-aramaHizi,saatYonunde?-aramaHizi:aramaHizi);
    return;
  }
  sonGormeZamani=simdi;
  int ileriHizi=ileriHizlari[secilenTaktik];
  // İki sensör aynı anda görürse ileri gidiyoruz.
  if (sol && sag) {
    motorlariSur(ileriHizi, ileriHizi);
  }
  // Yalnız sağ sensör görürse sağa dönüyoruz.
  else if (sag) {
    motorlariSur(60, -60);
  }
  // Geriye kalan durumda yalnız sol sensör görüyor.
  else {
    motorlariSur(-60, 60);
  }
}
