int Ledpin=2;

void setup() {
  // put your setup code here, to run once:
  pinMode (Ledpin, OUTPUT);
    }

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (Ledpin, HIGH);
  delay(200);
  digitalWrite (Ledpin, LOW);
  delay(200);
}
