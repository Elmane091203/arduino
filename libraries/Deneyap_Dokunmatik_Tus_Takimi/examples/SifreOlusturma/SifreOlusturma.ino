/*
 *   Şifre oluşturma örneği,
 *   
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   Önceden belirlenmiş 4 haneli şifreyi kullanıcı doğru bir şekilde tuş takımından basınca 
 *   seri terminalde "şifre doğru" yazısını yazdırmaktadır. Yanlış olunca "şifre yanlış" yazdırmaktadır.
 *   
 *   Basma süresine bağlı olarak birden fazla okuma yapabilir.
 *   
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *
 *   Bu örnek Deneyap Dokunmatik Tuş Takımı için oluşturulmuştur
 *      ------>  https://docs.deneyapkart.org/tr/content/contentDetail/deneyap-module-deneyap-soil-moisture-m38  <------
 *      ------>  https://github.com/deneyapkart/deneyap-dokunmatik-tus-takimi-arduino-library  <------ 
*/
#include <Deneyap_DokunmatikTusTakimi.h>        // Deneyap Dokunmatik Tuş Takımı kütüphanesi eklenmesi

int password[] = {0, 3, 0, 3};                  // Belirlenen şifre
int inputvalue[4];                              // Girilen şifre
int ArrayIndex = 0;                             // Sayaç

Keypad Keypad;                                  // Keypad için class tanımlanması

void IsPassCorrect();                           // IsPassCorrect fonksiyonunun prototipi 
void resetPass();                               // resetPass fonksiyonunun prototipi 

void setup() {
  Serial.begin(115200);                         // Seri haberleşme başlatılması
  Keypad.begin(0x0E);                           // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
}

void loop() {
  int keyword = Keypad.KeypadRead();            // Tuş takımına basılan değeri okuması
  if (keyword != 0xFF) {                        // Tuş takımına basıldığında
    inputvalue[ArrayIndex] = keyword;           // Birinci dizi sayısına tuş takımı değerini girilmesi
    ArrayIndex++;                               // Sayacı artır
    switch (ArrayIndex) {
    case 1:                                     // Birinci değer girilince ekrana * yazdırılması
      Serial.printf("*", inputvalue[0]);
      break;
    case 2:                                     // İkinci değer girilince ekrana * yazdırılması
      Serial.printf("*", inputvalue[1]);
      break;
    case 3:                                     // Üçüncü değer girilince ekrana * yazdırılması
      Serial.printf("*", inputvalue[2]);
      break;
    case 4:                                     // Dördüncü değer girilince ekrana * yazdırılması
      Serial.printf("*", inputvalue[3]);
      IsPassCorrect();
      ArrayIndex = 0;
      resetPass();
      break;
    }
  }
  delay(100);
}

void IsPassCorrect(){                           // Şifre doğru mu?
  if (password[0] == inputvalue[0] && password[1] == inputvalue[1] && password[2] == inputvalue[2] && password[3] == inputvalue[3]) {
    Serial.println(" şifre doğru");
    delay(500);
  } else{
    Serial.println(" şifre yanlış");
    }
  delay(2500);
}

void resetPass(){                             // Girilen şifre dizisinin sıfırlanması
    inputvalue[0] = NULL;
    inputvalue[1] = NULL;
    inputvalue[2] = NULL;
    inputvalue[3] = NULL;
    Serial.println(" yeniden şifre giriniz ");  
}
