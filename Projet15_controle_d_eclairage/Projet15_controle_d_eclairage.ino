#include <IRremote.h>
#define BotonO 0xFF6897
#define Boton1 0xFF30CF
#define Boton2 0xFF18E7
#define Boton3 0xFF7A85
int SensorIR = 11;
int Rele = 8;
IRrecv irrecv(SensorIR);
decode_results codigo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn();
  Serial.println("Enabled IRin");
  pinMode (Rele, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode(&codigo)){
    Serial.println(codigo.value, HEX);
    if (codigo.value == Boton2){
      digitalWrite(Rele, HIGH);  
    }
    delay(50); 
    if (codigo.value == Boton1){
      digitalWrite(Rele, LOW);
    }
    delay(50);
    irrecv.resume();
  }
  delay(100);

}
