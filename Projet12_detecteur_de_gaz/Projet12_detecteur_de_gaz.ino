int pin_led_rouge = 8;
int pin_led_verte = 9;
int pin_buzzer = 10;
int pin_d = 7;
int pin_a = A2;
int niveau_senseur = 300;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin_d, INPUT);
  pinMode(pin_a, INPUT);
  pinMode(pin_led_rouge, OUTPUT);
  pinMode(pin_led_verte, OUTPUT);
  pinMode(pin_buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valeur_digital = digitalRead(pin_d);
  int valeur_analogique = analogRead(pin_a);
  Serial.print("Dout : ");
  Serial.print(valeur_digital);
  Serial.print("Aout : ");
  Serial.print(valeur_analogique);
  if(valeur_analogique> niveau_senseur)
  {
    digitalWrite(pin_led_rouge, HIGH);
    digitalWrite(pin_led_verte, LOW);
    digitalWrite(pin_buzzer, HIGH);
  }
  else
  {
    digitalWrite(pin_led_rouge, LOW);
    digitalWrite(pin_led_verte, HIGH);
    digitalWrite(pin_buzzer, LOW);
  }
  delay(100);

}
