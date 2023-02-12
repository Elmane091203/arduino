int digitalPin = 4;
int analogPin = A0;
int digitalVal;
int analogVal;
void setup() {
  // put your setup code here, to run once:
  pinMode(digitalPin, OUTPUT);
  digitalWrite(digitalPin, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogVal = analogRead(analogPin);// lecture de l'interface analog
  if(analogVal<=600){// detection des flammes grace au capteur
    digitalWrite(digitalPin,HIGH);//La led s'all
  }else{
    digitalWrite(digitalPin, LOW);
  }
  delay(100);

}
