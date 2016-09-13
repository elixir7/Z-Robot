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
  pinMode(8, OUTPUT); //Left LED
  pinMode(2, OUTPUT); //Right LED

  tone(9, 3000, 1000);
  delay(2000);

  Serial.begin(9600);
}

byte wRight;
byte wLeft;

int wRightOld = 1;
int wLeftOld = 1;

int counter = 0;

void loop() {
  wRight = digitalRead(7);
  wLeft = digitalRead(5);

  forward();

  if(wLeft != wRight){
    Serial.println("wLeft != wRight");
    if(wLeft == 0){
      digitalWrite(8, HIGH);
      Serial.println("Turning Right");
      reverse();
      maneuver(1700, 1610, 300);
    }else if(wRight == 0){
      digitalWrite(2, HIGH);
      Serial.println("Turning Left");
      reverse();
      maneuver(1300, 1300, 300);
    }
    if((wLeft != wLeftOld) || (wRight != wRightOld)){
      counter++;
      Serial.println(counter);
      wLeftOld = wLeft;
      wRightOld = wRight;
      if(counter == 4){
       Serial.println("counter is 4, turning around");
       maneuver(1300, 1300, 1000);
       wLeft = 0;
       wRight = 0;
       counter = 0;
      }
    }else{
      Serial.println("Resetting counter");
      counter = 0;
    }
  }else if((wLeft == 0)&& (wRight== 0)){
    reverse ();
    maneuver(1300, 1300, 1000);
  }else{
    digitalWrite(8, LOW);
    digitalWrite(2, LOW);
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
