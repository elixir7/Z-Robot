#include <Servo.h>

Servo servoRight;
Servo servoLeft;

//Program that let's the bot escape a corner with the use of whiskers
void setup() {
  servoLeft.attach(11);
  servoRight.attach(10);
  
  pinMode(9, OUTPUT); //Speaker
  pinMode(7, INPUT); //Right whisker
  pinMode(5, INPUT); //Left whisker

  tone(9, 3000, 1000);
  delay(2000);

  Serial.begin(9600);
}

byte wRightOld = 0;
byte wLeftOld = 0;

void loop() {
  
  byte wRight = digitalRead(7);
  byte wLeft = digitalRead(5);

  forward();

  //Turn led on depending on whiskers
  if(wRight == 0){
    digitalWrite(2, HIGH);
    reverse();
    if(wRight != wLeftOld){
      maneuver(1300, 1300, 300);
    }else{
      maneuver(1300, 1300, 200);
    }
    wRightOld = wRight;
  }else if(wLeft == 0){
    digitalWrite(8, HIGH);
    reverse();
    if(wLeft != wRightOld){
      maneuver(1300, 1300, 300);
    }else{
      maneuver(1700, 1610, 200);
    }
    wLeftOld = wLeft;
  }else{
    digitalWrite(2, LOW);
    digitalWrite(8, LOW);
  }
}

void forward(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1390);
}

void reverse(){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1610);
  delay(1000);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void maneuver(int speedLeft, int speedRight, int msTime){
  servoLeft.writeMicroseconds(speedLeft);
  servoRight.writeMicroseconds(speedRight);
  if(msTime == -1){
    servoLeft.detach();
    servoRight.detach();
  }
  delay(msTime);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}


