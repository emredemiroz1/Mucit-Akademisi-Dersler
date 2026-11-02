// BU KOD MUCİT AKADEMİSİ İÇİN EMRE DEMİRÖZ HOCA TARAFINDAN HAZIRLANMIŞTIR.
// Ders: 05_Cizgi_Deneyleri
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
bool armed = false;
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
// PID hesabında ondalıklı sayılar gerektiği için float kullanıyoruz.
float birikenHata = 0;
float oncekiHata = 0;
float yumusakDegisim = 0;
bool ilkOlcum = true;
// Hedef kaybolunca eski hesapları siliyoruz.
void pidSifirla() {
  birikenHata = 0;
  oncekiHata = 0;
  yumusakDegisim = 0;
  ilkOlcum = true;
}
// Bu yardımcı bölüm robotun ne kadar dönmesi gerektiğini hesaplar.
float pidHesapla(float hata, float saniye, float kp, float ki, float kd, float sinir) {
  if (saniye <= 0 || saniye > 0.1) {
    pidSifirla();
    saniye = 0.01;
  }
  float degisim = 0;
  if (ilkOlcum == false) {
    degisim = (hata - oncekiHata) / saniye;
  }
  // Ani ölçüm sıçramalarını biraz yumuşatıyoruz.
  yumusakDegisim = 0.7 * yumusakDegisim + 0.3 * degisim;
  ilkOlcum = false;
  oncekiHata = hata;
  float yeniToplam = birikenHata + hata * saniye;
  yeniToplam = constrain(yeniToplam, -1.0, 1.0);
  // P: şimdiki hata. I: biriken hata. D: hatanın değişimi.
  float duzeltme = kp * hata + ki * yeniToplam + kd * yumusakDegisim;
  // Motor sınırdayken aynı yönde hata biriktirmiyoruz.
  if (abs(duzeltme) < sinir || duzeltme * hata < 0) {
    birikenHata = yeniToplam;
  }
  duzeltme = kp * hata + ki * birikenHata + kd * yumusakDegisim;
  return constrain(duzeltme, -sinir, sinir);
}
// Deney seçimi: 0 tek çizgi, 1 çizgi kenarı, 2 iki çizgi arası.
int SINGLE_CENTER = 0;
int SINGLE_EDGE = 1;
int TWO_BOUNDARIES = 2;
int MODE = 0; // Yukarıdaki üç deneyden birini seç.
// Iki cizgi arasi icin TWO_BOUNDARIES.
bool BLACK_HIGH=true;
int THRESHOLD=500;
int S[]={A0,A1,A2,A3,A4,A5,A6,A7};
// Soldan saga!
int lowRaw[8],highRaw[8];
bool validCalibration=false;
unsigned long calibrationAt;
bool calibrating=true;
unsigned long sonOlcumZamani=0,lostAt=0;
// setup: Kart açılınca yalnız bir kez çalışır.
void setup() {
  pinleriHazirla();
  calibrationAt=millis();
  for(int i=0;i<8;i++){
    lowRaw[i]=1023;
    highRaw[i]=0;
  }
}
// loop: Kart açık kaldıkça bu adımları tekrar tekrar yapar.
void loop() {
  unsigned long simdi=millis();
  if(calibrating){
    motorlariSur(0,0);
    // Robotu ELLE gezdir; her sensor siyah ve beyazi gorsun.
    for(int i=0;i<8;i++){
      int deger=analogRead(S[i]);
      lowRaw[i]=min(lowRaw[i],deger);
      highRaw[i]=max(highRaw[i],deger);
    }
    if(simdi-calibrationAt>=5000){
      calibrating=false;
      validCalibration=true;
      for(int i=0;i<8;i++)if(highRaw[i]-lowRaw[i]<100)validCalibration=false;
      Serial.println(validCalibration?"Kalibrasyon hazir":"Kalibrasyon gecersiz: resetle ve elle gezdir");
    }
    return;
  }
  if(butonaYeniBasildi()&&validCalibration){
    armed=!armed;
    pidSifirla();
    lostAt=0;
  }
  if(!armed){
    motorlariSur(0,0);
    return;
  }
  if(simdi-sonOlcumZamani<10)return;
  float gecenSaniye=(simdi-sonOlcumZamani)/1000.0f;
  sonOlcumZamani=simdi;
  float value[8];
  int starts[4],ends[4],groups=0;
  bool in=false;
  for(int i=0;i<8;i++){
    value[i]=constrain((analogRead(S[i])-lowRaw[i])*1000L/(highRaw[i]-lowRaw[i]),0L,1000L);
    if(!BLACK_HIGH)value[i]=1000-value[i];
    bool on=value[i]>=THRESHOLD;
    if(on&&!in){
      starts[groups]=i;
      ends[groups]=i;
      groups++;
    }
    if(on)ends[groups-1]=i;
    in=on;
  }
  bool found=false;
  float position=3500;
  if(MODE==TWO_BOUNDARIES){
    // Iki AYRI sensor grubu gorulmeli; tek cizgi gorunce ortalama uydurma.
    if(groups==2 && ends[0]<starts[1]){
      position=(ends[0]+starts[1])*500.0f;
      found=true;
    }
  }
  else if(groups==1 && ends[0]-starts[0]<6){
    if(MODE==SINGLE_CENTER){
      float sum=0,weighted=0;
      for(int i=starts[0];i<=ends[0];i++){
        sum+=value[i];
        weighted+=value[i]*i*1000.0f;
      }
      position=weighted/sum;
      found=true;
    }
    else{
      position=ends[0]*1000.0f+500;
      found=true;
    }
    // Siyah grubun sag kenari.
  }
  if(!found){
    motorlariSur(0,0);
    pidSifirla();
    if(lostAt==0)lostAt=simdi;
    if(simdi-lostAt>=300)armed=false;
    return;
  }
  lostAt=0;
  float hata=(position-3500)/3500.0f;
  float u=pidHesapla(hata,gecenSaniye,100,0,1.2f,90);
  int aramaHizi=80-(int)(35*abs(hata));
  motorlariSur(aramaHizi+(int)u,aramaHizi-(int)u);
}
