# 01 - Fansiz PID'siz Cizgi Izleyen

Bu model baslangic icin hazirlandi. PID hesabina girmeden, sensorlerin hangi tarafta cizgi gordugune bakar.

## Mantik

- Orta sensorler cizgiyi gorurse robot ileri gider.
- Sol sensorler cizgiyi gorurse robot sola duzeltme yapar.
- Sag sensorler cizgiyi gorurse robot saga duzeltme yapar.
- Hic sensor cizgi gormezse robot durur.

Bu kod, PID'li modele gecmeden once robotun mekanik ve sensor davranisini test etmek icin kullanilabilir.
