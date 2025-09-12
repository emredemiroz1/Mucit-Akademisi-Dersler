// Mucit Akademi Emre Hoca tarafından hazırlanmıştır...

// Bu program Arduino ' da 11, 12 ve 13. pinlere bağlanan LED'leri A0 pinine bağlı potansiyometreden gelen değere göre 
//  sırayla yakıp söndürür.

// Öğrenciler LED'lerin potansiyometre değerlerine göre sırayla yanıp söndüğünü görecekler :)


int potansiyometre;  // Potansiyometreden okunacak değeri tutan değişken

void setup()
{
    pinMode(A0, INPUT);   // Potansiyometre A0 pinine bağlı, giriş olarak ayarlandı

    pinMode(13, OUTPUT);  // 13. pine bağlı LED çıkış olarak ayarlandı
    pinMode(12, OUTPUT);  // 12. pine bağlı LED çıkış olarak ayarlandı
    pinMode(11, OUTPUT);  // 11. pine bağlı LED çıkış olarak ayarlandı
}

void loop()
{
    potansiyometre = analogRead(A0);  // Potansiyometreden 0–1023 arasında değer okunur

    // Eğer potansiyometre 0–255 aralığındaysa → tüm LED’ler sönük
    if (potansiyometre >= 0 && potansiyometre < 256)
    {
        digitalWrite(11, LOW);   // LED kapalı
        digitalWrite(12, LOW);   // LED kapalı
        digitalWrite(13, LOW);   // LED kapalı
    }
    // Eğer potansiyometre 256–511 aralığındaysa → sadece 11. pin LED yanar
    else if (potansiyometre >= 256 && potansiyometre < 512)
    {
        digitalWrite(11, HIGH);  // LED açık
        digitalWrite(12, LOW);   // LED kapalı
        digitalWrite(13, LOW);   // LED kapalı
    }
    // Eğer potansiyometre 512–767 aralığındaysa → sadece 12. pin LED yanar
    else if (potansiyometre >= 512 && potansiyometre < 768)
    {
        digitalWrite(11, LOW);   // LED kapalı
        digitalWrite(12, HIGH);  // LED açık
        digitalWrite(13, LOW);   // LED kapalı
    }
    // Eğer potansiyometre 768–1023 aralığındaysa → sadece 13. pin LED yanar
    else if (potansiyometre >= 768)
    {
        digitalWrite(11, LOW);   // LED kapalı
        digitalWrite(12, LOW);   // LED kapalı
        digitalWrite(13, HIGH);  // LED açık
    }
}

