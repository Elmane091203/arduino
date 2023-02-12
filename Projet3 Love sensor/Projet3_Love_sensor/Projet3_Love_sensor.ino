const int sensorPin = A0;
const float baselineTemp = 20.0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
for (int pinNumber = 2; pinNumber<5 ; pinNumber++){
  pinMode(pinNumber, OUTPUT);

}
}


void loop() {
  // put your main code here, to run repeatedly:
int sensorVal = analogRead(sensorPin);
Serial.print("Sensor Value: ");
Serial.print(sensorVal);
float voltage = (sensorVal/1023.0)*5.0;
Serial.print(", Volts: ");
Serial.print(voltage);
Serial.print(", Degrees C; ");
float temperature = (voltage - .5)*100;
Serial.print(temperature);
if (temperature < baselineTemp){
  digitalWrite (2,LOW);
  digitalWrite (3,LOW);
  digitalWrite (4,LOW);
}
else if(temperature>=baselineTemp +6 && temperature < baselineTemp+8){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
}
else if(temperature >=baselineTemp+8 && temperature< baselineTemp+10){
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  
}
else if(temperature>=baselineTemp +15){
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
}
delay(1);
}
