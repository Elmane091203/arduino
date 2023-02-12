// import the library #include <Servo.h> // create an instance of the servo library Servo myServo; const int piezo = A0; const int switchPin = 2; const int yellowLed = 3; const int greenLed = 4; const int redLed = 5; //defines LED's and piezo's pins. // variable for the piezo value int knockVal; // variable for the switch value int switchVal; // variables for the high and low limits of the knock value const int quietKnock = 10; const int loudKnock = 100; // variable to indicate if locked or not boolean locked = false; // how many valid knocks you've received int numberOfKnocks = 0;
 #include <Servo.h> 
 // create an instance of the servo library
 Servo myServo;
 const int piezo = A0;
 const int switchPin = 2;
 const int yellowLed = 3;
 const int greenLed = 4;
 const int redLed = 5;
 int knockVal;
 int switchVal;
 const int quietKnock = 10;
 const int loudKnock = 100;
 boolean locked = false;
 int numberOfKnocks = 0;
void setup() {
  // put your setup code here, to run once:
  myServo.attach(9);
  // make the LED pins outputs 
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  // set the switch pin as an input 
  pinMode(switchPin, INPUT);
  // start serial communication for debugging 
  Serial.begin(9600); 
  // turn the green LED on
  digitalWrite(greenLed, HIGH);
  // move the servo to the unlocked position 
  myServo.write(0); 
  // print status to the serial monitor
  Serial.println("the box is unlocked!"); 
}

void loop() {
  // put your main code here, to run repeatedly:
  // if the box is unlocked
  if(locked == false){ // read the value of the switch pin
    switchVal = digitalRead(switchPin); // if the button is pressed, lock the box 
    if(switchVal == HIGH){ // set the locked variable to "true" 
      locked = true; // change the status LEDs 
      digitalWrite(greenLed,LOW);
      digitalWrite(redLed,HIGH); 
      // move the servo to the locked position 
      myServo.write(90); 
      // print out status 
      Serial.println("the box is locked!");
      // wait for the servo to move into position 
      
      }   
  }
}
