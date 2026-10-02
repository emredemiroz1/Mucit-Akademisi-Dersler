# 💻 Satır kodlamaya başlangıç

[⬅️ Algoritma](02_Algoritmik_Dusunme.md) · [📚 Ders notları](README.md) · [LED uygulamaları ➡️](04_LED_Uygulamalari.md)

## 🎯 Neler öğreneceğim?

Arduino programının yapısını, temel komutları ve sık karşılaşılan yazım hatalarını öğreneceksin.

## 🏠 Programın iki ana bölümü

```cpp
void setup() {
  // Baslangic hazirliklari burada yapilir.
}

void loop() {
  // Surekli tekrarlanacak islemler burada yazilir.
}
```

- **setup():** Kart açıldığında veya sıfırlandığında bir kez çalışır. Pin ayarlarını burada yaparız.
- **loop():** İçindeki işlemler tamamlanınca yeniden başlar.
- **void:** Fonksiyonun bir değer döndürmediğini belirtir.

Blok kodlamadaki başlangıç hazırlıklarını `setup()`, sürekli tekrar eden davranışı `loop()` ile ilişkilendirebilirsin.

## 🧰 Temel komutlar

| Komut | Ne yapar? | Örnek |
|---|---|---|
| `pinMode` | Pinin çalışma modunu ayarlar | `pinMode(11, OUTPUT);` |
| `digitalWrite` | Dijital çıkışı HIGH veya LOW yapar | `digitalWrite(11, HIGH);` |
| `digitalRead` | Dijital giriş durumunu okur | `digitalRead(7)` |
| `delay` | Verilen milisaniye kadar bekler | `delay(1000);` |
| `Serial.println` | Seri Monitör'e bilgi gönderir | `Serial.println(durum);` |

**1000 milisaniye = 1 saniye.** `delay(500)` yarım saniye beklemektir.

> [!NOTE]
> `delay` boyunca programın bu akışındaki sonraki komutlar bekler. Bu sırada döngüde yeni bir buton okuması yapılmaz. Uzun beklemeler, butona tepkiyi geciktirebilir.

## 💡 Tam bir örnek

```cpp
const int led = 11;  // LED'in pin numarasi.

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);  // Yak.
  delay(1000);             // Bir saniye bekle.
  digitalWrite(led, LOW);   // Sondur.
  delay(1000);             // Bir saniye bekle.
}
```

`led` adı 11 sayısını temsil eder. `const`, bu tanımlı değerin kod içinde değiştirilmesini engeller.

**Bir tur:** Yak → 1 saniye bekle → söndür → 1 saniye bekle. Beklemelerin toplamı 2 saniyedir; diğer komutların da küçük çalışma süreleri vardır.

## ✍️ İşaretleri tanıyalım

- **;**: Birçok komut ve tanımın sonuna konur.
- **{ }**: Fonksiyonun veya koşulun içine ait komutları gruplar.
- **( )**: Fonksiyon parametrelerini veya koşulu içerir.
- **//**: Satırın devamını yorum yapar. Açıklama program komutu olarak çalışmaz.

Her satırın sonuna noktalı virgül konmaz. Örneğin `void loop() {` veya `if (durum == LOW) {` satırlarına eklenmez.

## 🔀 Bir koşulun yapısı

```cpp
if (durum == LOW) {
  // Kosul dogruysa burasi calisir.
} else {
  // Kosul yanlissa burasi calisir.
}
```

Bu parça sözdizimini gösterir; tam programda `durum` önce tanımlanıp girişten okunmalıdır.

| İşaret | Anlamı |
|---|---|
| `=` | Değer atama: `int durum = HIGH;` |
| `==` | Eşitliği karşılaştırma: `durum == LOW` |
| `!=` | Eşit değil mi? |

## 🎯 Sen dene

1. LED örneğindeki pin numarasını D13'e göre değiştir.
2. Yanma süresini 500 ms, sönme süresini 1500 ms yap.
3. Kendi koduna her işlemi açıklayan yorum satırı ekle.

## 🛠️ Sık yapılan hatalar

| Hata | Kontrol |
|---|---|
| `digitalwrite` yazmak | Doğrusu `digitalWrite`; büyük harfler önemlidir |
| Eksik `;` | Komutun sonunu kontrol et |
| Eksik `}` | Açılan parantezlerin eşini bul |
| Değişken adını farklı yazmak | `led` ve `Led` aynı ad değildir |
| `delay(1)` ile bir saniye beklediğini sanmak | Bu yalnızca 1 ms'dir |

<details>
<summary>🧠 Kontrol sorusu: pinMode neden setup içine yazılır?</summary>

Pinin görevini başlangıçta belirlemek yeterlidir. Normalde aynı ayarı her döngüde tekrar yapmamız gerekmez.

</details>

📖 [Arduino dil başvurusu](https://docs.arduino.cc/language-reference/).
