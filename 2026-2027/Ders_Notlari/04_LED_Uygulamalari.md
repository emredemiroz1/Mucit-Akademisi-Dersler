# 💡 LED uygulamaları

[⬅️ Satır kodlama](03_Satir_Kodlamaya_Baslangic.md) · [📚 Ders notları](README.md) · [Buton ve anahtar ➡️](05_Buton_ve_Anahtar.md)

## 🎯 Neler öğreneceğim?

LED'in görevini, ışığın açık ve kapalı durumlarını ve birden fazla LED'i sırayla kontrol etmeyi öğreneceksin.

## 🔎 LED nedir?

LED, elektrik enerjisini ışığa dönüştüren bir diyottur. Gösterge lambalarında, ekranlarda ve aydınlatmalarda kullanılır.

Harici LED'de anot ve katot yönü önemlidir. Yeni, bacakları kesilmemiş bir LED'de uzun bacak genellikle anot, kısa bacak katottur. Bağlantıyı bileşenin işaretleriyle kontrol et.

**Harici LED devresinde akımı sınırlayan uygun seri direnç kullanılır.** Direnç değeri besleme gerilimine, LED'in ileri gerilimine ve hedef akıma göre seçilir. MERBoard üzerindeki hazır LED devrelerini derslerde doğrudan ilgili pinlerden kontrol ederiz.

## 📍 LED pinlerimiz

**D11, D12 ve D13.** Bu örneklerde `HIGH` LED'i yakar, `LOW` söndürür.

## 🔁 Yakıp söndürme

```cpp
void setup() {
  pinMode(11, OUTPUT);
}

void loop() {
  digitalWrite(11, HIGH);
  delay(1000);
  digitalWrite(11, LOW);
  delay(1000);
}
```

**Tahmin et:** Her iki beklemeyi 250 ms yaparsan yanıp sönme hızlanır mı?

## 🚶 Yürüyen ışık

Bu örnekte her adımda bir LED yanar. Önceki LED, sıradaki yakılmadan önce söndürülür.

```cpp
void setup() {
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

void loop() {
  digitalWrite(11, HIGH);
  delay(1000);
  digitalWrite(11, LOW);

  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);

  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
}
```

| Adım | D11 | D12 | D13 | Bekleme |
|---|---|---|---|---|
| 1 | Açık | Kapalı | Kapalı | 1 saniye |
| 2 | Kapalı | Açık | Kapalı | 1 saniye |
| 3 | Kapalı | Kapalı | Açık | 1 saniye |

Döngü bitince sıra yeniden D11'den başlar.

## 🎯 Sen dene

- 🟢 **Başlangıç:** D12 LED'ini 2 saniye yakıp 1 saniye söndür.
- 🟡 **Orta:** Yürüyen ışığın yönünü D13 → D12 → D11 olarak değiştir.
- 🟠 **İleri:** D11 ve D13 birlikte yanarken D12 kapalı olsun. Bir saniye sonra yalnızca D12 yansın. Bu iki durumu tekrar et.

## 🛠️ Sık yapılan hatalar

- Önceki LED'i söndürmeden diğerini yakmak: LED'ler birikerek açık kalır.
- `pinMode` ayarlarını yalnızca bir LED için yapmak.
- Yanma ve sönme sürelerini karıştırmak.

<details>
<summary>🧠 Kontrol sorusu: Üç HIGH komutunu arka arkaya yazarsam yürüyen ışık olur mu?</summary>

Aralarında görünür bekleme ve söndürme adımları yoksa üç LED kısa sürede birlikte yanar. Yürüyen ışık için sırayı, süreyi ve kapalı durumları planlamalısın.

</details>

🔗 [Mevcut LED uygulamalarına geç](../Arduino_Kodlari/01_LED_Uygulamalari/)

📖 [Arduino digitalWrite](https://docs.arduino.cc/language-reference/en/functions/digital-io/digitalwrite/) · [Arduino delay](https://docs.arduino.cc/language-reference/en/functions/time/delay/).
