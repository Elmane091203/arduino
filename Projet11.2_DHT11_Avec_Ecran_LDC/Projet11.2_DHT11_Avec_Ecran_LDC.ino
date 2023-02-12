#include <LiquidCrystal.h>
#include "DHT.h"
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#define PinCapteur 2
#define Type DHT11
DHT dht (PinCapteur, Type);
const int RelaisPin = 6;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  dht.begin();
  pinMode(RelaisPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  float humidite = dht.readHumidity();
  float temperature = dht.readTemperature();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tempera = ");
  lcd.print(temperature);
  lcd.setCursor(0,1);
  lcd.print("Humidite = ");
  lcd.print(humidite);
  if(temperature>=34 && temperature<=90)
  {
    digitalWrite(RelaisPin, HIGH);
  }
  else
  {
    digitalWrite(RelaisPin, LOW);
  }
  delay(1000);
}
