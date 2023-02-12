int buttons[6];
int notes[]={262,294,330,349};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int PushedKeyValue = analogRead(A0);
  Serial.println(PushedKeyValue);
  if(PushedKeyValue==1023){
    tone(8,notes[0]);
  }
  else if(PushedKeyValue>=990 && PushedKeyValue<=1010){
    tone(8,notes[1]);
  
  }
  else if(PushedKeyValue>=505 && PushedKeyValue<=515){
    tone(8,notes[2]);
  }
  else if(PushedKeyValue>=5 && PushedKeyValue<=10){
    tone(8,notes[3]);
  }
  else{
    noTone(8);
  }
}
