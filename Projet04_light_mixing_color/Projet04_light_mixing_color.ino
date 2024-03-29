const int greenLEDPin = 9;
const int blueLEDPin = 10;
const int redLEDPin = 11;
const int redSensorPin = A0;
const int blueSensorPin = A2;
const int greenSensorPin = A1;
int redValue = 0;
int greenValue = 0;
int blueValue = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(greenLEDPin, OUTPUT);
pinMode(blueLEDPin, OUTPUT);
pinMode(redLEDPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;
pinMode(greenLEDPin, OUTPUT);
pinMode(blueLEDPin, OUTPUT);
pinMode(redLEDPin, OUTPUT);
greenSensorValue =  analogRead(greenSensorValue);
delay(5);
blueSensorValue =  analogRead(blueSensorValue);
Serial.print("Raw Sensor Value \t Red :");
Serial.print(redSensorValue);
Serial.print("\t Green");
Serial.print(greenSensorValue);
Serial.print("\t Blue");
Serial.print(blueSensorValue);
redValue= redSensorValue/4;
greenValue =  greenSensorValue/4;
Serial.print("Mapped Sensor Values\t Red:");
Serial.print(redValue);
Serial.print("\t Green:");
Serial.print(greenValue);
Serial.print("\t Blue:");
Serial.print(blueValue);
analogWrite(redLEDPin, redValue);
analogWrite(greenLEDPin, greenValue);
analogWrite(blueLEDPin, blueValue);
}
