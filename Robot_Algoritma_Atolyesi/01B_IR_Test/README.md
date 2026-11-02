# 📡 Kumanda çalışıyor mu? Önce motorlar kapalı!

**Amaç:** D4'ün gerçekten kumanda başlangıç modülüne bağlı olduğunu ve çıkış biçimini öğrenmek. Pin D4 şu an varsayımdır.

## 1 · İki farklı parçayı ayıralım

| Parça | Çıkış | Bu atölye kodu |
|---|---|---|
| Kumanda komutunu çözen başlangıç modülü | Gitten sonra sürekli 1, durdan sonra sürekli 0 | Doğrulanırsa birleşik örneklerle uyumlu |
| Ham IR alıcısı (ör. televizyon alıcı gözü) | Çok kısa darbeler, boşta 1 de olabilir | **Uyumlu değil:** protokol çözme ve komut kodlarını öğrenme gerekir |

Bir TV kumandasındaki tuş numarası, D4'teki lojik 1 ile aynı şey değildir. Darbeli/toggle/ters seviyeli modül de bu örnekle doğrudan kullanılamaz. Ham alıcı varsa modelini ve komutlarını belirleyip ayrı çözücü uyarlayın; `kumandaTestiTamam` açmayın.

## 2 · Bağlantıyı doğrula

Kart şemasından sinyal pinini bul. GND ortak olmalı, çıkış gerilimi karta uygun olmalı. `INPUT` girişi açıkta bırakılmamalı; modül çıkışı açık kolektörse gerekli direnç bağlantısını kendi veri sayfasına göre yap. Kablo sökülmesi güvenilir biçimde algılanmaz.

## 3 · Test kodunu yükle

[IR test eskizi](01B_IR_Test.ino): motorlar sürekli kapalı. Seri Monitör **115200**. D11 giriş seviyesini gösterir; 100 ms boyunca 1 kaldığında kısa ses duyulur. Bu yalnızca **seviye testi**, kumanda protokolü çözme testi değildir. 100 ms seri çıktısı ham IR darbelerini incelemeye yeterli değildir.

| Eylem | Beklenen modül çıkışı | Gözlediğim |
|---|---|---|
| Kumandadan dur | Sürekli 0, D11 sönük | |
| Kumandadan git ve tuşu bırak | Sürekli 1, D11 yanık | |
| Tekrar dur | Sürekli 0 | |

Yanlış tuşları da dene: git sayılmamalı. Açılışta 1 varsa önce dur göndermeden birleşik kod başlamaz. Dalgalanma, boşta sürekli 1, yalnız kısa darbe veya ters davranış varsa modül tipini netleştirmeden motorlu örneğe geçme.

## 4 · Duvar görevi, ardından sumo

Sharp eşiklerini ölç → D4 testini tamamla → ilgili örnekte iki READY iznini aç → tekerlekler havadayken git/dur dene → düşük hızlı zemin deneyi yap. Duvar örneğinde engel sonrası tekrar gitmeden önce dur gönder. Sumo örneğinde D7 sayıyı, D2 yönü belirler; LED'ler sayıyı gösterir.

[🏠 Bütün ders akışı](../README.md)
