#include<Servo.h>
Servo myServo;
const int piezo = A1;
const int switchPin = 8;
const int yellowLed = 9;
const int greenLed = 10;
const int redLed = 11;
int knockVal;
int switchVal;
const int quietKnock = 10;
const int loudKnock = 100;
boolean locked = false;
int numberOfKnocks = 0;
void setup() {
  // put your setup code here, to run once:
  myServo.attach(12);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(switchPin, INPUT);
  Serial.println("The box is unloked!");

}

void loop() {
  // put your main code here, to run repeatedly:
  if(locked == false){
    switchVal = digitalRead(switchPin);
    if(switchVal == HIGH){
      myServo.write(90);
      Serial.println("The box is locked!");
      delay(1000);
    }
  }
  
  if(locked == true){
    knockVal = analogRead(piezo);
    if(numberOfKnocks<3 && knockVal>0){
      if(checkForKnock (knockVal)==true){
        numberOfKnocks++;
      }
      Serial.print(3-numberOfKnocks);
      Serial.print(" more knocks to go");
    }
    if(numberOfKnocks>=3){
      locked = false;
      myServo.write(0);
      delay(200);
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, HIGH);
      Serial.println("The box is unlocked!");
    }
  }
}
  boolean checkForKnock(int value){
    if(value> quietKnock && value < loudKnock){
      digitalWrite(yellowLed,HIGH);
      delay(1000);
      digitalWrite(yellowLed, LOW);
      Serial.print("Valid knock of value");
      Serial.println(value);
      return true;
    }
    else{
      Serial.print("Bad knock value");
      Serial.println(value);
      return false;
    }
  }
