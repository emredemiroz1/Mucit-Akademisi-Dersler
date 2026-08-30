# Profesyonel Cizgi Izleyen

Bu klasor yeni donemde denenecek profesyonel cizgi izleyen robot modelleri icin hazirlandi.

Amac; fanli, fansiz, PID'li ve PID'siz farkli robot modellerini ayni duzen icinde denemek ve gelistirmektir.

## ROBOMER pin bilgisi

- Sag motor: D5, D6
- Sol motor: D9, D10
- Cizgi sensorleri: A0, A1, A2, A3, A4, A5, A6, A7
- Sensor LED / emitter pini: D2
- Fan cikisi: D2 taslak olarak kullanildi
- Buton: D7
- Anahtar: D4
- Buzzer: D3
- LED'ler: D11, D12, D13

Not: Fanli modellerde fan surucusu icin D2 kullanildi. Sensorde emitter pini aktif kullaniliyorsa fan icin farkli bir cikis secilmelidir.

## Klasorler

- `01_Fansiz_PID_Siz`: Basit karar mantigi ile cizgi izleyen.
- `02_Fansiz_PID_Li`: PID kontrol ile daha duzgun takip yapan model.
- `03_Fanli_PID_Siz`: Fan cikisi acik, PID kullanmayan model.
- `04_Fanli_PID_Li`: Fan cikisi acik, PID kullanan hizli model.
- `99_Eski_Kod_Notlari`: 2025-2026 kodlarindan alinan teknik notlar.

## Ayar yaparken

1. Once sensorleri siyah ve beyaz zeminde test edin.
2. `siyahEsik` degeri uygun degilse degistirin.
3. Robot ters yone gidiyorsa motor yon fonksiyonlarindaki HIGH/LOW taraflarini kontrol edin.
4. PID'li kodlarda once `Kp`, sonra gerekirse `Kd` ayarini degistirin.
5. Fanli modelde fan piste fazla bastiriyorsa fan hizini dusurun.
