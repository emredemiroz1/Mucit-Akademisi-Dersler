# 🧠 Algoritmik düşünme

[⬅️ Kart tanıtımı](01_RoboMer_Kart_Tanitimi.md) · [📚 Ders notları](README.md) · [Satır kodlama ➡️](03_Satir_Kodlamaya_Baslangic.md)

## 🎯 Neler öğreneceğim?

Kod yazmadan önce işi küçük adımlara ayırmayı, karar vermeyi ve tekrarları planlamayı öğreneceksin.

## 🧭 Algoritma nedir?

**Algoritma**, bir işi tamamlamak için belirlediğimiz adımlardır.

Robot “Güzel bir ışık gösterisi yap” cümlesinden hangi LED'i ne zaman yakacağını çıkaramaz. Hangi çıkışın çalışacağını ve işlem sırasını açıkça belirtmelisin.

## 💡 Bir LED'i yakıp söndürelim

1. LED pinini çıkış olarak ayarla.
2. LED'i yak.
3. Bir saniye bekle.
4. LED'i söndür.
5. Bir saniye bekle.
6. İkinci adıma dön.

İlk adım başlangıç hazırlığıdır. Diğer adımlar sürekli tekrarlanan işlemdir.

🔍 **Düşün:** İkinci beklemeyi çıkarırsan LED'in sönük kaldığını rahatça görebilir misin?

## 🧩 Üç temel yapı

| Yapı | Anlamı | Robot örneği |
|---|---|---|
| ➡️ Sıralama | Adımları belirlenen sırayla uygula | Yak → bekle → söndür |
| 🔀 Koşul | Duruma göre farklı işlem yap | Butona basılıysa LED'i yak |
| 🔁 Tekrar | Bir işlemi yeniden uygula | LED'i sürekli yanıp söndür |

## 🔘 Koşul örneği

**Eğer** butona basılıysa LED'i yak. **Değilse** LED'i söndür.

İki durumu da düşünmelisin. Yalnızca “basılıysa yak” dersen, buton bırakıldığında LED'in sönmesini sağlayan bir işlem olmayabilir.

## 📝 Koddan önce karar tablosu

| Durum | Yapılacak işlem |
|---|---|
| Buton basılı | LED açık |
| Buton bırakılmış | LED kapalı |

Birden fazla giriş varsa **aynı anda gerçekleşen durumlarda hangi kuralın önce uygulanacağını** belirle. Örneğin robotun durdurma butonu, hareket komutundan daha öncelikli olabilir.

## 🎯 Sen dene

1. D11 LED'ini iki saniye yakıp bir saniye söndüren algoritmayı yaz.
2. D11 → D12 → D13 sırasıyla, her seferinde bir LED yakmak için adımları oluştur.
3. Butona basılıyken ışık açık, bırakılmışken kapalı olacak karar tablosunu çiz.

**Bu aşamada kod yazmadan önce defterine adımları yaz.**

## 🛠️ Sık yapılan hatalar

- “LED'leri sırayla yak” deyip süreyi ve söndürme adımlarını belirtmemek.
- Bir koşulun yalnızca bir sonucunu düşünmek.
- Robotun başlangıç durumunu veya tekrarın nereden başlayacağını unutmak.

<details>
<summary>🧠 Kontrol sorusu: LED'i yakıp hemen söndürürsek neden ışığı seçemeyebiliriz?</summary>

LED çok kısa süre açık kalır. İşlemler hızlı tekrarlandığında gözümüz ayrı yanma ve sönme adımlarını ayırt edemeyebilir. Görünür bir yanıp sönme için uygun bekleme süreleri gerekir.

</details>

⭐ **Kendine sor:** “Bu algoritmayı başka bir öğrenci okusa aynı davranışı oluşturabilir mi?”
