# 02 - Fansiz PID'li Cizgi Izleyen

Bu model PID kontrol kullanir. Cizginin tam ortadan ne kadar saptigini hesaplar ve motor hizlarini buna gore ayarlar.

## Ayarlanacak degerler

- `Kp`: Robot cizgiden uzaklasinca ne kadar sert tepki verecek?
- `Ki`: Uzun sureli kaymalari telafi eder. Baslangicta kucuk tutulur.
- `Kd`: Ani savrulmalari azaltir.
- `temelHiz`: Robotun duz giderken hizidir.

Once `Kp` ile baslayin. Robot titriyorsa `Kp` degerini dusurun veya `Kd` degerini artirin.
