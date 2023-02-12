#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>
#include <SPI.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(10, 9);
Servo sg90;
constexpr uint8_t greenLed = 7;
constexpr uint8_t redLed = 6;
constexpr uint8_t servoPin = 8;
constexpr uint8_t buzzerPin = 5;
char initial_password[4] = {'1','2','3','4'};
String tagUID = "92 0C 81 63";
char password[4];
boolean RFIDMode = true;
char key_pressed = 0;
uint8_t i = 0;
const byte rows = 4;
const byte columns = 4;
char hexaKeys[rows][columns]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte row_pins[rows] = { A0, A1, A2, A3};
byte column_pins[columns] = {2, 1, 0};
Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);
void setup() {
  // put your setup code here, to run once:
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  sg90.attach(servoPin);
  sg90.write(0);
  lcd.init();
  lcd.backlight();
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (RFIDMode == true){
    lcd.setCursor(0, 0);
    lcd.print("Porte verrouer");
    lcd.setCursor(0, 1);
    lcd.print("Scanner le badge");
    if(!mfrc522.PICC_IsNewCardPresent()){
      return;
    }
    if(!mfrc522.PICC_ReadCardSerial()){
      return;
    }
    String tag = "";
    for(byte j = 0; j < mfrc522.uid.size;j++){
      tag.concat(String(mfrc522.uid.uidByte[j]<0x10? " 0": " "));
      tag.concat(String(mfrc522.uid.uidByte[j], HEX));
    }
    tag.toUpperCase();
    if (tag.substring(1) == tagUID)
    {
      lcd.clear();
      lcd.print("Badge correspond");
      digitalWrite(greenLed, HIGH);
      delay(3000);
      digitalWrite(greenLed, LOW);
      lcd.clear();
      lcd.print("Entre le Passe");
      lcd.setCursor(0, 1);
      RFIDMode = false;
    }
    else
    {
      lcd.clear();
      lcd.print("Mauvaise carte");
      lcd.setCursor(0, 1);
      lcd.print("Access Refuser");
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(redLed, HIGH);
      delay(3000);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(redLed, LOW);
      lcd.clear();      
    }
  }
  if(RFIDMode == false)
  {
    key_pressed = keypad_key.getKey();
    if (key_pressed)
    {
      password[i++] = key_pressed;
      lcd.print("*");
    }
    if (i == 4)
    {
      delay(200);
      if(!(strncmp(password, initial_password, 4)))
      {
        lcd.clear();
        lcd.print("Pass Accepter!");
        sg90.write(90);
        digitalWrite(greenLed, HIGH);
        delay(3000);
        digitalWrite(greenLed, LOW);
        sg90.write(0);
        lcd.clear();
        i = 0;
        RFIDMode = true;
      }
      else
      {
        lcd.clear();
        lcd.print("Mauvaise passe");
        digitalWrite(buzzerPin, HIGH);
        digitalWrite(redLed, HIGH);
        delay(3000);
        digitalWrite(buzzerPin, LOW);
        digitalWrite(redLed, LOW);
        lcd.clear();
        i = 0;
        RFIDMode = true;
      }
    }
  }

}
