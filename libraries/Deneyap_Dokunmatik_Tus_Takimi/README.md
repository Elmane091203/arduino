# Deneyap Keypad Arduino Library
[FOR TURKISH VERSION](docs/README_tr.md) ![trflag](https://github.com/deneyapkart/deneyapkart-arduino-core/blob/master/docs/tr.png)

***** Add photo ****

Arduino library for Deneyap Keypad

## :mag_right:Specifications 
- `Product ID` **M37**, **mpv1.0**
- `MCU` MSP430G2352
- `Weight` 
- `Module Dimension` 25,4 mm x 50,8 mm
- `I2C address` 0x0E, 0x4C, 0x71, 0x72

| Address |  | 
| :---      | :---     |
| 0x0E | default address |
| 0x4C | address when ADR1 pad is shorted |
| 0x71 | address when ADR2 pad is shorted |
| 0x72 | address when ADR1 and ADR2 pads are shorted |

## :closed_book:Documentation
[Deneyap Keypad](https://docs.deneyapkart.org/en/content/contentDetail/deneyap-module-deneyap-10-channel-capacitive-touch)

[Deneyap Keypad Shematic](https://cdn.deneyapkart.org/media/upload/userFormUpload/cSEa06t8wPdTh5Jfws3hIy83dHGlIcI7.pdf)

[Deneyap Keypad Mechanical Drawing](https://cdn.deneyapkart.org/media/upload/userFormUpload/DzoOykFQ86tRQ0IDaZCqCrPQaAdaZVKl.pdf)

[How to install a Arduino Library](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries)

## :pushpin:Deneyap Keypad
This Arduino library allows you to use Deneyap Keypad with I2C peripheral. You can use this library in your projects with any Arduino compatible board with I2C peripheral.

## :globe_with_meridians:Repository Contents
- `/docs ` README_tr.md and product photos
- `/examples ` Examples with .ino extension sketches
- `/src ` Source files (.cpp .h)
- `keywords.txt ` Keywords from this library that will be highlighted in the Arduino IDE
- `library.properties ` General library properties for the Arduino package manager

## Version History
1.0.2 - update sketch(SifreOlusturma) and texts info

1.0.1 - update library, add sketch

1.0.0 - initial release

## :rocket:Hardware Connections
- Deneyap Keypad and Board can be connected with I2C cable
- or 3V3, GND, SDA and SCL pins can be connected with jumper cables

| Keypad | Function | Board pins | 
|:--- |   :---  | :---|
|3.3V | Power   |3.3V |      
|GND  | Ground  | GND | 
|SDA  | I2C Data  | SDA pin |
|SCL  | I2C Clock | SCL pin |
|SBWTCK | Debug | no connection |
|SBWTDIO| Debug | no connection |
|BUT0 |0. Capacitive touch pin|any GPIO pin|
|BUT1 |1. Capacitive touch pin|any GPIO pin|
|BUT2 |2. Capacitive touch pin|any GPIO pin|
|BUT3 |3. Capacitive touch pin|any GPIO pin|
|BUT4 |4. Capacitive touch pin|any GPIO pin|
|BUT5 |5. Capacitive touch pin|any GPIO pin|
|BUT6 |6. Capacitive touch pin|any GPIO pin|
|BUT7 |7. Capacitive touch pin|any GPIO pin|
|BUT8 |8. Capacitive touch pin|any GPIO pin|
|BUT9 |9. Capacitive touch pin|any GPIO pin|

## :bookmark_tabs:License Information
Please review the [LICENSE](https://github.com/deneyapkart/deneyap-dokunmatik-tus-takimi-arduino-library/blob/master/LICENSE) file for license information.
