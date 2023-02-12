/*
 *   Rakam Yazdırma örneği,
 *
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   Dokunmatik tuş takımından basılınca okunan değerin seri monitore yazdırmaktadır.
 *
 *   Basma süresine bağlı olarak birden fazla okuma yapabilir.
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *
 *   Bu örnek Deneyap Dokunmatik Tuş Takımı için oluşturulmuştur
 *      ------>  https://docs.deneyapkart.org/tr/content/contentDetail/deneyap-module-deneyap-soil-moisture-m38  <------
 *      ------>  https://github.com/deneyapkart/deneyap-dokunmatik-tus-takimi-arduino-library  <------ 
*/

#include <Deneyap_DokunmatikTusTakimi.h>            // Deneyap Dokunmatik Tuş Takımı kütüphanesi eklenmesi

Keypad TusTakimi;                                   // Keypad için class tanımlanması

void setup() {
  Serial.begin(115200);                             // Seri haberleşme başlatılması
  if (!TusTakimi.begin(0x0E)) {                     // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
    Serial.println("I2C bağlantısı başarısız ");    // I2C bağlantısı başarısız olursa seri terminale yazdırılması
    while (1);
  }
}

void loop() {
  int keypadDeger = TusTakimi.KeypadRead();         // Tuş takımına basılan değeri okuması
  if (keypadDeger != 0xFF)
    Serial.println(keypadDeger);                    // Tuş takımından okunan değerin seri monitore yazılması
  delay(100);
}
