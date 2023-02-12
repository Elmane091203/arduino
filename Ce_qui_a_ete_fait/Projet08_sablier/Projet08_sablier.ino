const int PinInterruptor = 8;
unsigned long PreviousTime = 0;
int InterruptorState = 0;
int PreviousStateInterruptor = 0;
int Led = 2;
long TimeIntervalocadaLed = 500;
int c = 0;
void setup() {
  // put your setup code here, to run once:
  for(int x=2; x<8;x++){
    pinMode(x,OUTPUT);
  }
  pinMode(PinInterruptor, INPUT);
}

void loop() {
  unsigned long ActualTime = millis();
  if(ActualTime-PreviousTime>TimeIntervalocadaLed){
    PreviousTime = ActualTime;
    digitalWrite(Led, HIGH);
    Led++;
    if(Led==7){
      
    }
  }
  InterruptorState = digitalRead(PinInterruptor);
  if(InterruptorState!=PreviousStateInterruptor){
    for(int x = 2; x < 8; x++){
      digitalWrite(x,LOW);
    }
    Led = 2;
    PreviousTime = ActualTime;
  }
  PreviousStateInterruptor = InterruptorState;
  // put your main code here, to run repeatedly:

}
