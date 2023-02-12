#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
const int switchPin = 6;
int switchState=0;
int prevSwitchState = 0;
int reply;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(switchPin, INPUT);
  lcd.print("Demander  encore");
  lcd.setCursor(0,1);
  lcd.print("Crystal Ball!");
}

void loop() {
  // put your main code here, to run repeatedly:
  switchState = digitalRead(switchPin);
  if(switchState != prevSwitchState){
    if(switchState == LOW){
      reply=random(8);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ISI dit:");
      lcd.setCursor(0,1);
      switch(reply){
        case 0:
        lcd.print("Certainement");
        break;
        case 1:
        lcd.print("Excellence");
        break;
        case 2:
        lcd.print("Innovation");
        break;
        case 3:
        lcd.print("Technologie");
        break;
        case 4:
        lcd.print("Sience et Tech");
        break;
        case 5:
        lcd.print("L'avenir");
        break;
        case 6:
        lcd.print("NTIC");
        break;
        case 7:
        lcd.print("Developpement");
        break;
      }
    }
  }
  prevSwitchState = switchState;
}
