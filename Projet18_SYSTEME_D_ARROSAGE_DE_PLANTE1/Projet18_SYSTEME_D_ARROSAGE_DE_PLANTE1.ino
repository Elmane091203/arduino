
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#define NOTE_C6 1047
#define NOTE_C3 131
#define NOTE_G3 196
int levelSensorPin = A0;
int moistureSensorPin = A1;
int audioPin = 2;
int soggyLEDPin = 3;
int moistsoilLEDPin = 4;
int drysoilLEDPin = 5;
int pumpLEDPin = 6;
int pumpPin = 7;
int pumpPin2 = 8;
int levelSensorValue;
int moistureSensorValue;
int j = 0;
const char *string_table[] = {
    "                       Bienvenue!  ",
    "  Niv Reserv Bas    Nivea Reserv Bas",
    "                        Sol sec",
    "                     Sol humide",
    "                     Sol Detremper",
    "                  Pompe Allumé ",
    " PLANETE POMPE    ", " System Arrosage ",
    " Veuillez Patienter! ",
    "                              Moteur Marche ",
    "                              Moteur Arret "};
RTC_DS1307 RTC;
LiquidCrystal_I2C lcd(0x27, 20, 4);
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  Wire.begin();
  RTC.begin();
  if (!RTC.isrunning())
  {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  pinMode(audioPin, OUTPUT);
  pinMode(soggyLEDPin, OUTPUT);
  pinMode(moistsoilLEDPin, OUTPUT);
  pinMode(drysoilLEDPin, OUTPUT);
  pinMode(pumpLEDPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(string_table[6]);
  lcd.setCursor(0, 1);
  lcd.print(string_table[7]);
  lcd.setCursor(0, 3);
  lcd.print(string_table[0]);
}
void loop()
{
  DateTime myRTC = RTC.now();
  int H = myRTC.hour();
  int M = myRTC.minute();
  int S = myRTC.second();
  levelSensorValue = analogRead(levelSensorPin);
  moistureSensorValue = analogRead(moistureSensorPin);
  if (levelSensorValue > 600)
  {
    lcd.clear();
    lcd.setCursor(0, 3);
    lcd.print(string_table[1]);
    for (int i = 0; i < 2; i++)
    {
      tone(audioPin, NOTE_G3, 200);
      delay(200);
      tone(audioPin, NOTE_C3, 200);
      delay(200);
      noTone(audioPin);
      pinMode(pumpPin, LOW);
    }
  }
  if (moistureSensorValue >= 800)
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(string_table[2]);
    lcd.setCursor(0, 0);
    lcd.print(string_table[6]);
    digitalWrite(drysoilLEDPin, LOW);
    digitalWrite(moistsoilLEDPin, LOW);
    digitalWrite(soggyLEDPin, LOW);
    digitalWrite(pumpPin, LOW);
    tone(audioPin, NOTE_C6, 100);
    delay(250);
    noTone(audioPin);
  }
  if ((moistureSensorValue < 700) && (moistureSensorValue >= 300))
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(string_table[3]);
    lcd.setCursor(0, 0);
    lcd.print(string_table[6]);
    digitalWrite(drysoilLEDPin, HIGH);
    digitalWrite(moistsoilLEDPin, HIGH);
    digitalWrite(soggyLEDPin, LOW);
    digitalWrite(pumpLEDPin, HIGH);
    delay(250);
  }
  if (moistureSensorValue < 300)
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(string_table[4]);
    lcd.setCursor(0, 0);
    lcd.print(string_table[6]);
    digitalWrite(drysoilLEDPin, HIGH);
    digitalWrite(moistsoilLEDPin, LOW);
    digitalWrite(soggyLEDPin, HIGH);
    delay(100);
  }
  if ((H == 16) && (M == 50) && (S == 00))
  {
    while (moistureSensorValue >= 700)
    {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(string_table[8]);
      lcd.setCursor(0, 3);
      lcd.print(string_table[5]);
      digitalWrite(pumpPin, LOW);
      digitalWrite(pumpLEDPin, HIGH);
      delay(10000);
      moistureSensorValue = analogRead(moistureSensorPin);
    }
    digitalWrite(pumpPin, LOW);
    digitalWrite(pumpLEDPin, LOW);
  }
}
void RightHour()
{
  DateTime Now = RTC.now();
  String clock_date = "  Date: ";
  String clock_hour = "   Time: ";
  int _day = Now.day();
  int _month = Now.month();
  int _year = Now.year();
  clock_date += fixZero(_day);
  clock_date += "/";
  clock_date += fixZero(_month);
  clock_date += "/";
  clock_date += _year;
  int _hour = Now.hour();
  int _minute = Now.minute();
  int _second = Now.second();
  clock_hour += fixZero(_hour);
  clock_hour += ":";
  clock_hour += fixZero(_minute);
  clock_hour += ":";
  clock_hour += fixZero(_second);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(clock_date);
  lcd.setCursor(0, 1);
  lcd.print(clock_hour);
  delay(500);
}
String fixZero(int i)
{
  String ret;
  if (i < 10)
    ret += "0";
  ret += i;
  return ret;
}
