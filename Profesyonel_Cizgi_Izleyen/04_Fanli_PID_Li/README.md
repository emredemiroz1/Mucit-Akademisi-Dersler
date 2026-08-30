# 04 - Fanli PID'li Cizgi Izleyen

Bu model hizli ve daha profesyonel denemeler icindir. Fan acikken PID ile cizgi takip eder.

## Ayar sirasi

1. Once fan kapaliyken `Kp`, `Kd` ve `temelHiz` ayarlarini deneyin.
2. Sonra `fanHizi` degerini dusukten yuksege artirin.
3. Robot virajlarda savruluyorsa `temelHiz` veya `fanHizi` degerini azaltin.
4. Robot cizgiye gec tepki veriyorsa `Kp` degerini biraz artirin.

Fan cikisi taslak olarak `D2` secildi. Sensorde emitter pini de `D2` kullaniyorsa fan pinini degistirin.
