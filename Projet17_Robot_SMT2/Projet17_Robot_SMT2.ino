#include<Servo.h>
#include<NewPing.h>
const int LeftMotorForward = 7; // Moteur Gauche Avant
const int LeftMotorBackward = 6; // Moteur Gauche Arrière
const int RightMotorForward = 4;// Moteur Droite Avant
const int RightMotorBackward = 5;//Moteur Droite Arrière
int pos=0;
//sensor pins
#define trig_pin A1//analog input 1
#define echo_pin A2 //analog input 2
#define maximum_distance 300
boolean goesForward = false; //va de l'avant
int distance = 200;
NewPing sonar(trig_pin, echo_pin, maximum_distance) ; //fonction du capteur
Servo servo_motor; //1e nom du servo
Servo myservo;
void setup(){
  pinMode (RightMotorForward, OUTPUT);
  pinMode (LeftMotorForward, OUTPUT);
  pinMode (LeftMotorBackward, OUTPUT);
  pinMode (RightMotorBackward, OUTPUT);
  servo_motor.attach (10) ; //1e nom du servo
  myservo.attach (13);
  servo_motor.write (115);
}
void loop(){
  int distanceRight = 0;
  int distanceLeft = 0;
  delay (50);
  if (distance <= 20)(
  movestop();
  delay (300);
  myservo.write(170);
  delay (300)
  myservo.write(50);
  delay (300);
  myservo.write (170) ;
  delay (300);
  myservo.write (50);
  delay (300);
  moveBackward();
  delay(400);
  moveStop();
  delay(300);
  distanceRight = lookRight();
  delay(300);
  distanceLeft = lookLeft();
  delay(300);
  digitalWrite(RightMotorForward, LOW);
  delay (500);
  digitalWrite (LeftMotorForward, HIGH);
  digitalWrite (RightMotorForward, HIGH) ;
  digitalWrite (LeftMotorBackward, LOW);
  digitalWrite (RightMotorBackward, LOW);
}
void turnleft ()(
  digitalWrite (LeftMotorBackward, HIGH);
  digitalWrite (RightMotorForward, HIGH);
  digitalWrite (LeftMotorForward, LOW);
  digitalWrite (RightMotorBackward, LOW);
  delay (500);
  digitalWrite (LeftMotorForward, HIGH) ;
  digitalWrite (RightMotorForward, HIGH);
  digitalWrite (LeftMotorBackward, LOW);
  digitalWrite (RightMotorBackwad, LOW);
}
void moveForward () {
  if(!goesForward) (
  goesForward=true;
  digitalWrite (LeftMotorForward, HIGH) ;//Moteur droit avant : haut
  digitalWrite (RightMotorForward, HIGH) ;//Moteur gauche avant : haut
  digitalWrite (LeftMotorBackward, LOW) ; //Moteur gauche arrière BAS
  digitalWrite (RightMotorBackward, LOW) ;//Moteur droit vers l'arrière BAS
}
void moveBackward (){
  goesForward=false;
  digitalWrite (LeftMotorBackward, HIGH);
  digitalWrite (RightMotorBackward, HIGH);
  digitalWrite (Leftmotorforward, LOW);
  digitalWrite (RightMotorForward, LOW);
}
void turnRight (){
  digitalWrite (LeftMotorForward, HIGH);
  digitalWrite (RightMotorBackward, HIGH);
  digitalWrite (LeftMotorBackward, LOW);
  digitalWrite (RightMotorForward, LOW);
  delay(100);
  servo_motor.write(l15)
  return distance;
  delay (100);
}
int readPing(){
  delay (70);
  int cm = sonar.ping_cm();
  if (cm=0) {
  cm-250; }
  return cm;
}
void moveStop(){
digitalWrite (RightMotorForward, LOW);
digitalWrite (LeftMotorForward, LOW);
digitalWrite (RightMotorBackward, LOW);
digitalWrite (LeftMotorBackward, LOW);
}
