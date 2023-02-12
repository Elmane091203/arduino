# Deneyap Dokunmatik Tuş Takımı Arduino Kütüphanesi

***** Fotoğraf eklenecek ****

Deneyap Dokunmatik Tuş Takımı için Arduino kütüphanesidir.

## :mag_right:Özellikler 
- `Ürün ID` **M37**, **mpv1.0**
- `MCU` MSP430G2352
- `Ağırlık`
- `Modul Boyutları` 25,4 mm x 50,8 mm
- `I2C Adres` 0x0E, 0x4C, 0x71, 0x72

| Adres |  | 
| :--- | :---     |
| 0x0E | varsayılan adres |
| 0x4C | ADR1 kısa devre yapıldığındaki adres |
| 0x71 | ADR2 kısa devre yapıldığındaki adres |
| 0x72 | ADR1 ve ADR2 kısa devre yapıldığındaki adres |

## :closed_book:Dokümanlar
[Deneyap Dokunmatik Tuş Takımı](https://docs.deneyapkart.org/tr/content/contentDetail/deneyap-module-deneyap-10-channel-capacitive-touch)

[Deneyap Dokunmatik Tuş Takımı Şematik](https://cdn.deneyapkart.org/media/upload/userFormUpload/cSEa06t8wPdTh5Jfws3hIy83dHGlIcI7.pdf)

[Deneyap Dokunmatik Tuş Takımı Teknik Resim](https://cdn.deneyapkart.org/media/upload/userFormUpload/DzoOykFQ86tRQ0IDaZCqCrPQaAdaZVKl.pdf)

[Arduino IDE'de Kütüphane Nasıl İndirilir](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries)

## :pushpin:Deneyap Dokunmatik Tuş Takımı
Bu Arduino kütüphanesi Deneyap Dokunmatik Tuş Takımının I2C çevre birimi ile kullanılmasını sağlar. Arduino ile uyumlu, I2C çevre birimine sahip herhangi bir geliştirme kartı ile bu kütüphaneyi projelerinizde kullanabilirsiniz.

## :globe_with_meridians:Repo İçeriği
- `/docs` README_tr.md ve ürün fotoğrafları
- `/examples` .ino uzantılı örnek uygulamalar
- `/src` kütüphane için .cpp ve .h uzantılı dosyalar
- `keywords.txt` Arduino IDE'de vurgulanacak anahtar kelimeler
- `library.properties` Arduino yöneticisi için genel kütüphane özellikleri

## Sürüm Geçmişi
1.0.2 - örnek(SifreOlusturma) ve metinler bilgileri güncellendi

1.0.1 - kütüphane güncellendi, örnek uygulama eklendi

1.0.0 - ilk sürüm

## :rocket:Donanım Bağlantıları
- Deneyap Dokunmatik Tuş Takımı ile kullanılan geliştirme kartı I2C kablosu ile bağlanabilir
- veya jumper kablolar ile 3V3, GND, SDA ve SCL bağlantıları yapılabilir. 

| Dokunmatik Tuş Takımı | Fonksiyon| Kart pinleri |
| :---     | :---   |   :---  |
| 3.3V     |3.3V Besleme Gerilimi| 3.3V    |
| GND      | Toprak |GND      |
| SDA      |Çift Yönlü Veri Hattı| SDA pini |
| SCL      |Veri Hatta Zaman Senkronivasyon İşareti| SCL pini|
|SBWTCK |Debug|bağlantı yok|
|SBWTDIO|Debug|bağlantı yok|
|BUT0 |0 Nolu Buton Kapasitif Algılama Arayüz Pini|herhangi GPIO pini|
|BUT1 |1 Nolu Buton Kapasitif Algılama Arayüz Pini|herhangi GPIO pini|
|BUT2 |2 Nolu Buton Kapasitif Algılama Arayüz Pini|herhangi GPIO pini|
|BUT3 |3 Nolu Buton Kapasitif Algılama Arayüz Pini|herhangi GPIO pini|
|BUT4 |4 Nolu Buton Kapasitif Algılama Arayüz Pini|herhangi GPIO pini|
|BUT5 |5 Nolu Buton Kapasitif Algılama Arayüz Pini|herhangi GPIO pini|
|BUT6 |6 Nolu Buton Kapasitif Algılama Arayüz Pini|herhangi GPIO pini|
|BUT7 |7 Nolu Buton Kapasitif Algılama Arayüz Pini|herhangi GPIO pini|
|BUT8 |8 Nolu Buton Kapasitif Algılama Arayüz Pini|herhangi GPIO pini|
|BUT9 |9 Nolu Buton Kapasitif Algılama Arayüz Pini|herhangi GPIO pini|

## :bookmark_tabs:Lisans Bilgisi 
Lisans bilgileri için [LICENSE](https://github.com/deneyapkart/deneyap-dokunmatik-tus-takimi-arduino-library/blob/master/LICENSE) dosyasını inceleyin.