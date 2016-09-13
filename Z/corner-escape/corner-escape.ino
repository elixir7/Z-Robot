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

byte wRight;
byte wLeft;

byte wRightOld = 1;
byte wLeftOld = 1;

int counter = 0;

void loop() {
  
  wRight = digitalRead(7);
  wLeft = digitalRead(5);

  forward();

  //Right whisker activated
  if(wRight == 0){
    Serial.println("Right whisker activated, turning left");
    //turn right led on
    digitalWrite(2, HIGH);
    
    reverse();
    //Turn Left
    maneuver(1300, 1300, 300);
    
    counter++;
    Serial.println(counter);

    if(counter == 3){
      Serial.println("Stuck, turning 180deg");
      //Turn 180deg
      maneuver(1300, 1300, 500);
      counter = 0;
    }
    
    if(wRight == wRightOld){
      Serial.println("wRight == wRightOld, resetting counter");
      counter = 0;
      wRightOld = 1;
    }else{
      wRightOld = wRight;
    }
    
  }else if(wLeft == 0){
    Serial.println("Left whisker activated, turning right");
    //turn left led on
    digitalWrite(8, HIGH);
    
    reverse();
    //turn right
    maneuver(1700, 1610, 300);

    counter++;
    Serial.println(counter);

    if(counter == 3){
      Serial.println("Stuck, turning 180deg");
      //Turn 180deg
      maneuver(1300, 1300, 1000);
      counter = 0;
    }
    
    if(wLeft == wLeftOld){
      Serial.println("wLeft == wLeftOld, resetting counter");
      counter = 0;
      wLeftOld = 1;
    }else{
      wLeftOld = wLeft;
    }
    
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


