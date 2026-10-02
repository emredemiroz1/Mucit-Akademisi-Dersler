# 🔘 Buton ve anahtar

[⬅️ LED uygulamaları](04_LED_Uygulamalari.md) · [📚 Ders notları](README.md)

## 🎯 Neler öğreneceğim?

Buton ile anahtar arasındaki farkı, dijital giriş okumayı ve aynı anda birden fazla koşul olduğunda öncelik belirlemeyi öğreneceksin.

## ↔️ Aralarındaki fark

**Buton**, basılı tutulduğu süre boyunca durum değiştirir ve bırakılınca başlangıç konumuna döner.

**Anahtar**, seçtiğin konumda kalır. Program bu konuma göre davranış seçebilir.

| Eleman | Sınıfımızdaki pin | Örnek kullanım |
|---|---|---|
| Buton | D7 | Basılıyken bir LED'i yakmak |
| Anahtar | D2 | İki çalışma modu arasında seçim yapmak |

> [!NOTE]
> Repodaki eski anahtar kodu D4 kullanır. Buradaki ders notlarında sınıfımızdaki **D2** bağlantısı esas alınır.

## 📥 digitalRead ne yapar?

`digitalRead(pin)`, dijital girişin `HIGH` veya `LOW` olduğunu döndürür. Tek başına “sağ”, “sol” veya “basılı” bilgisi vermez. Bu anlamı bağlantı şekline göre belirleriz.

## 🧲 INPUT_PULLUP neden kullanılır?

`INPUT_PULLUP`, pinin dahili pull-up direncini etkinleştirir. Böylece giriş bağlantısızken yüksek seviyeye çekilir. Buton pin ile GND arasına bağlıysa:

| Buton durumu | Okunan değer |
|---|---|
| Bırakılmış | HIGH |
| Basılı | LOW |

> [!IMPORTANT]
> Bu tablo **pin–GND arasına bağlı buton** içindir. Kartındaki devre farklıysa sonuç değişebilir. Önce Seri Monitör'den ölç, sonra koşulunu yaz.

## 🔍 Önce değerleri gözlemleyelim

```cpp
const int buton = 7;
const int anahtar = 2;

void setup() {
  pinMode(buton, INPUT_PULLUP);
  pinMode(anahtar, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Buton: ");
  Serial.print(digitalRead(buton));
  Serial.print(" | Anahtar: ");
  Serial.println(digitalRead(anahtar));
  delay(100);
}
```

Seri Monitör hızını **9600 baud** seç. Butona basıp bırak ve anahtarı iki konuma getir. Okunan değerleri not et:

| Deney | Gördüğüm değer |
|---|---|
| Buton bırakılmış | … |
| Buton basılı | … |
| Anahtar sağda | … |
| Anahtar solda | … |

`HIGH` genellikle ekranda **1**, `LOW` **0** görünür. İki anahtar konumu aynı değeri veriyorsa bağlantıyı öğretmeninle kontrol et.

## 💡 Butonla tek LED kontrolü

Aşağıdaki örnek, basılınca **LOW** okunan buton bağlantısına göredir.

```cpp
const int buton = 7;
const int led = 13;

void setup() {
  pinMode(buton, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  int butonDurumu = digitalRead(buton);

  if (butonDurumu == LOW) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
```

Her döngüde giriş yeniden okunur. Butonun hem basılı hem bırakılmış durumunda çıkışın ne olacağı belirtilmiştir.

## 🔀 Birden fazla koşulda öncelik

Bir girişin diğerinden öncelikli olması gerekiyorsa karar sırası önemlidir:

```text
Eğer öncelikli koşul doğruysa:
    Öncelikli işlemi uygula.
Değilse eğer ikinci koşul doğruysa:
    İkinci işlemi uygula.
Değilse:
    Diğer duruma ait işlemi uygula.
```

`if – else if – else` zincirinde ilk doğru koşulun bölümü çalışır. Ayrı ayrı `if` kullanırsan birden fazla bölüm çalışabilir ve sonraki komut, öncekinin çıkışını değiştirebilir.

## 🎯 Sen dene

1. Buton örneğini D11 LED'i ile çalıştır.
2. Anahtarın iki konumuna iki farklı LED durumu belirle. Önce karar tablosunu yaz.
3. Birden fazla giriş kullanırken hangi kuralın öncelikli olacağını bir cümleyle açıkla.

⭐ Önce giriş değerlerini ölç. Ardından kendi algoritmanı ve kodunu yaz.

## 🛠️ Sık yapılan hatalar

- `LOW` değerini her bağlantıda “bırakılmış” sanmak.
- Anahtarın sağ konumunun her zaman `HIGH` olacağını varsaymak.
- Buton bırakıldığında LED'i söndüren kısmı unutmak.
- Girişi yalnızca `setup` içinde okuyup yeni durumları takip edememek.
- Uzun `delay` nedeniyle butonun hemen okunmasını beklemek.

<details>
<summary>🧠 Kontrol sorusu: Neden sağ konumun değerini önce ölçüyoruz?</summary>

Sağ ve sol, anahtarın fiziksel konumlarıdır. HIGH ve LOW ise elektriksel seviyelerdir. Aralarındaki eşleştirme bağlantıya göre değişir.

</details>

🔗 [Mevcut buton uygulaması](../Arduino_Kodlari/05_Buton_ve_Dijital_Giris/ders_5_buton_led_kontrol/) · [Dijital giriş uygulamaları](../Arduino_Kodlari/05_Buton_ve_Dijital_Giris/)

📖 [Arduino digitalRead](https://docs.arduino.cc/language-reference/en/functions/digital-io/digitalread/) · [Arduino pinMode](https://docs.arduino.cc/language-reference/en/functions/digital-io/pinMode/).
