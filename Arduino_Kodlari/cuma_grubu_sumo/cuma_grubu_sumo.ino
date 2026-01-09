/*
    SOL sensör  -> A0
    SAĞ sensör  -> A7

  Taktikler (butona basınca değişir):
    0 = Dur
    1 = Hedef yakınsa ileri
    2 = Hedef hangi taraftaysa o tarafa dön
    3 = Hedef yoksa arama yap, hedef bulunca yaklaş

  Start:
    START_PIN HIGH olunca çalışır.
*/

// ---------------- PINLER ----------------
#define START_PIN 4
#define BUTON_PIN 7

// Motor pinleri (senin eski kodunla aynı)
#define SOL_ILERİ  5
#define SOL_GERİ   6
#define SAG_ILERİ  9
#define SAG_GERİ   10

// Sharp sensör pinleri
#define SHARP_SOL A0
#define SHARP_SAG A7

// ---------------- AYARLAR ----------------
int taktik = 0;
bool basladi = false;

int HIZ = 200;

// "Hedef var" demek için eşik (cm)
// GP2Y0A21 genelde ~10-80 cm çalışır. 30 cm iyi başlangıç.
int ESİK_CM = 30;

// ---------------- MOTOR SÜRME ----------------
void motor(int solIleri, int solGeri, int sagIleri, int sagGeri)
{
  analogWrite(SOL_ILERİ, solIleri);
  analogWrite(SOL_GERİ,  solGeri);
  analogWrite(SAG_ILERİ, sagIleri);
  analogWrite(SAG_GERİ,  sagGeri);
}

void dur()   { motor(0,0,0,0); }
void ileri() { motor(HIZ,0,HIZ,0); }

// sağa dön: sol ileri, sağ geri
void sagaDon()
{
  motor(HIZ,0,0,HIZ);
  delay(120);
  dur();
}

// sola dön: sol geri, sağ ileri
void solaDon()
{
  motor(0,HIZ,HIZ,0);
  delay(120);
  dur();
}

// arama: sağa doğru yay çiz (sol hızlı, sağ yavaş)
void ara()
{
  motor(200,0,120,0);
  delay(150);
}

// ---------------- SHARP OKUMA ----------------
// Daha stabil olsun diye 5 kez okuyup ortalamasını alıyoruz
int analogOrtalama(int pin)
{
  long toplam = 0;
  for (int i = 0; i < 5; i++)
  {
    toplam += analogRead(pin);
    delay(2);
  }
  return toplam / 5;
}

// Yaklaşık cm hesaplama (GP2Y0A21 için)
// Not: Her sensörde biraz fark olur, bu yüzden eşik değerini test ederek ayarla.
int sharpCm(int pin)
{
  int deger = analogOrtalama(pin);          // 0-1023
  float volt = deger * (5.0 / 1023.0);      // 0-5V

  // Çok düşük voltajda formül bozulur; güvenlik:
  if (volt < 0.4) return 999;

  // Yaklaşık dönüşüm (pratikte iş görür)
  float cm = 27.86 / (volt - 0.42);

  // mantıklı aralık
  if (cm < 5) cm = 5;
  if (cm > 150) cm = 150;

  return (int)cm;
}

// ---------------- BUTONLA TAKTİK DEĞİŞTİR ----------------
void taktikDegistir()
{
  if (digitalRead(BUTON_PIN) == LOW)
  {
    delay(200);          // buton zıplamasını azaltır
    taktik++;
    if (taktik > 3) taktik = 0;

    while (digitalRead(BUTON_PIN) == LOW) { } // bırakana kadar bekle
  }
}

// ---------------- SETUP ----------------
void setup()
{
  pinMode(START_PIN, INPUT);
  pinMode(BUTON_PIN, INPUT);

  pinMode(SOL_ILERİ, OUTPUT);
  pinMode(SOL_GERİ, OUTPUT);
  pinMode(SAG_ILERİ, OUTPUT);
  pinMode(SAG_GERİ, OUTPUT);

  pinMode(SHARP_SOL, INPUT);
  pinMode(SHARP_SAG, INPUT);

  dur();
}

// ---------------- LOOP ----------------
void loop()
{
  taktikDegistir();

  // Start kontrol
  if (digitalRead(START_PIN) == HIGH) basladi = true;
  if (!basladi) { dur(); return; }

  // Mesafeleri oku (cm)
  int solCm = sharpCm(SHARP_SOL);
  int sagCm = sharpCm(SHARP_SAG);

  // -------- TAKTİKLER --------
  if (taktik == 0)
  {
    // 0: Dur
    dur();
  }
  else if (taktik == 1)
  {
    // 1: Yakınsa saldır
    if (solCm < ESİK_CM || sagCm < ESİK_CM) ileri();
    else dur();
  }
  else if (taktik == 2)
  {
    // 2: Hangi tarafta yakınsa oraya dön
    if (solCm < ESİK_CM && sagCm < ESİK_CM) ileri();
    else if (solCm < ESİK_CM) solaDon();
    else if (sagCm < ESİK_CM) sagaDon();
    else dur();
  }
  else if (taktik == 3)
  {
    // 3: Hedef yoksa ara, hedef varsa yaklaş
    if (solCm < ESİK_CM || sagCm < ESİK_CM)
    {
      if (solCm < sagCm) solaDon();
      else sagaDon();
      ileri();
    }
    else
    {
      ara();
    }
  }
}
