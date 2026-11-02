![RoboMer keşif rehberi; temsili robot çizimi](../../gorseller/robomer-rehber.svg)

# 🤖 RoboMer kartını tanıyalım

[📚 Ders notları](README.md) · [Sonraki ders: Algoritma ➡️](02_Algoritmik_Dusunme.md)

## 🎯 Neler öğreneceğim?

- Kartın hangi bölümünün programı çalıştırdığını,
- pin numarasının ne anlama geldiğini,
- giriş ve çıkış elemanlarının farkını öğreneceksin.

## 🗺️ Robotun bilgi yolculuğu

| 👀 1. Bilgi al | 🧠 2. Karar ver | 💡 3. Harekete geç |
| --- | --- | --- |
| Buton ve sensörler | Arduino Nano üzerindeki program | LED, buzzer ve motor sürücüsü |
| “Butona basıldı mı?” | “Basılmışsa LED'i yak.” | “Işığı aç!” |

> [!TIP]
> **Dedektif görevi:** Karta bak ve üç farklı eleman bul. Hangisi bilgi veriyor, hangisi bir işi gerçekleştiriyor? Üstteki robot resmi temsili bir rehber çizimidir; kart bağlantı şeması değildir.

## 🧩 Kartın içinde neler var?

**MERBoard**, robotik projelerinde kullandığımız geliştirme kartıdır. Üzerindeki **Arduino Nano** programını çalıştırır. **TB6612 motor sürücüsü**, Arduino'nun kontrol sinyallerine göre DC motorları sürer.

Bir robotu düşün: Butondan veya sensörden bilgi alır, programındaki kurallara göre karar verir, ardından LED veya motor gibi bir çıkışı kontrol eder.

**Pin**, karta bilgi göndermek veya karttan sinyal almak için kullanılan bağlantı noktasıdır. Kodda yazdığın pin numarası, hangi bağlantıyı kullanacağını belirtir.

## 📍 Sınıfımızdaki bağlantılar

| Eleman | Pin | Görevi |
|---|---|---|
| 💡 LED'ler | D11, D12, D13 | Işık üretir — çıkış |
| 🔊 Buzzer | D3 | Ses üretir — çıkış |
| 🔘 Buton | D7 | Basılma bilgisini verir — giriş |
| ↔️ Derslerde kullandığımız anahtar | D2 | Konum bilgisi verir — giriş |
| ⚙️ Sağ motorun kontrol girişleri | D5, D6 | Motor sürücüsünü kontrol eder |
| ⚙️ Sol motorun kontrol girişleri | D9, D10 | Motor sürücüsünü kontrol eder |
| 📊 Analog sensör girişleri | A0–A7 | Analog değer okumada kullanılır |

> [!NOTE]
> Kitaptaki pin listesinde D2 dijital sensör, D4 taktik anahtarı olarak belirtilmiştir. **Bizim derslerde kullandığımız anahtar D2'ye bağlıdır.** Repodaki eski anahtar örneği D4 kullanır. Her uygulamada kendi kartının bağlantısını kontrol et.

> [!TIP]
> Kart üzerinde “D11” yazar. Arduino kodunda bu dijital pini genellikle **11** olarak yazarız. Analog pinler için **A0** gibi adlar kullanılır.

Klasik Nano'da A6 ve A7 yalnızca analog giriş olarak kullanılabilir. Motor bağlantısı ile motorun kontrol pini aynı şey değildir: motorlar motor sürücüsüne bağlanır.

## 🚪 Giriş mi, çıkış mı?

**Giriş:** Arduino'nun dışarıdan bilgi aldığı bağlantıdır. Buton ve sensörler örnektir.

**Çıkış:** Arduino'nun bir elemanı kontrol etmek için sinyal gönderdiği bağlantıdır. LED ve buzzer örnektir.

🔍 Evindeki otomatik gece lambasında ışık sensörü giriş, lamba ise çıkıştır.

## 💻 Küçük bir örnek

```cpp
void setup() {
  pinMode(11, OUTPUT);  // D11 pinini cikis olarak ayarla.
}

void loop() {
  digitalWrite(11, HIGH);  // D11 LED'ini yak.
}
```

`pinMode` pinin görevini, `digitalWrite` ise çıkışın durumunu belirler.

## 🎯 Sen dene

1. Kart üzerinde LED, buzzer ve butonu bul.
2. Bunların pin numaralarını kod açmadan söyle.
3. Yukarıdaki örneği D12 LED'ini yakacak şekilde değiştir.

## 🛠️ Sık yapılan hatalar

- LED D11'e bağlıyken kodda başka pin kullanmak.
- LED pinini çıkış olarak ayarlamayı unutmak.
- Harici motoru Arduino'nun sinyal pinine doğrudan bağlamak.

<details>
<summary>🧠 Kendini kontrol et: Buton neden giriş elemanıdır?</summary>

Arduino butonu kontrol etmek yerine butonun durumunu **okur**. Bu nedenle buton bir giriş elemanıdır.

</details>

📖 Kaynak: RoboMer ders kitabı, sınıf bağlantı bilgileri ve [Arduino Nano belgeleri](https://docs.arduino.cc/hardware/nano/).
