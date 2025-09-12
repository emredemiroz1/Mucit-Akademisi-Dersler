// Mucit Akademi Emre Hoca tarafından hazırlanmıştır...

// Bu program Arduino ' da 11, 12 ve 13. pinlere bağlanan LED'leri sırayla yakıp söndürür.
// Öğrenciler LED'lerin sırayla yanıp söndüğünü görecekler :)



void setup() {
  // LED pinlerini çıkış (OUTPUT) olarak ayarlıyoruz
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  // İlk LED yanacak
  digitalWrite(led1, HIGH);  // LED1’i yak
  delay(500);                // 0,5 saniye bekle
  digitalWrite(led1, LOW);   // LED1’i söndür
  delay(500);                // 0,5 saniye bekle

  // İkinci LED yanacak
  digitalWrite(led2, HIGH);  // LED2’yi yak
  delay(500);
  digitalWrite(led2, LOW);   // LED2’yi söndür
  delay(500);

  // Üçüncü LED yanacak
  digitalWrite(led3, HIGH);  // LED3’ü yak
  delay(500);
  digitalWrite(led3, LOW);   // LED3’ü söndür
  delay(500);
}
