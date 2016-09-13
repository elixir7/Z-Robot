#include <Servo.h>

Servo servoRight;
Servo servoLeft;

void setup() {
  servoLeft.attach(11);
  servoRight.attach(10);

  pinMode(7, INPUT); //Right whisker
  pinMode(5, INPUT); //Left whisker
  pinMode(9, OUTPUT); //Speaker
  pinMode(8, OUTPUT); //Left LED
  pinMode(2, OUTPUT); //Right LED
  Serial.begin(9600);

  tone(9, 3000, 1000);
  delay(2000);

  forward(15);
  maneuver(1520, 1390, 1000);
  maneuver(1700, 1470, 4200);
  forward(49);
  maneuver(1650, 1480, 1000);
  maneuver(1520, 1390, 4200);
  
}

void loop() {
  byte wRight = digitalRead(7);
  byte wLeft = digitalRead(5);

  //Turn led on depending on whiskers
  if(wRight == 0){
    digitalWrite(2, HIGH);
  }else if(wLeft == 0){
    digitalWrite(8, HIGH);
  }else{
    digitalWrite(2, LOW);
    digitalWrite(8, LOW);
  }
}

void forward(double distance){
  double speed = 0.16;
  double time = (distance/100) / speed;
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1390);
  delay(time*1000);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500); 
}

void turn(String direction){
  if(direction == "right"){
    for(int speed = 0; speed <= 110; speed += 2){
      Serial.print(speed);
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1390 + speed);
      delay(40);
    }
  }else if(direction == "left"){
    for(int speed = 0; speed <= 50; speed+2){
      servoLeft.writeMicroseconds(1700 - speed);
      servoRight.writeMicroseconds(1390);
    }
  }
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

void playMusic(){
   tone(9, 1568, 500);
  delay(500);
  tone(9, 1568, 500);
  delay(500);
  tone(9, 1568, 500);
  delay(500);
  tone(9, 1568, 500);
  delay(500);
  
  tone(9, 1865, 300);
  delay(300);
  tone(9, 2093, 300);
  delay(300);

  tone(9, 1568, 500);
  delay(500);
  tone(9, 1568, 500);
  delay(500);
  tone(9, 1568, 500);
  delay(500);
  tone(9, 1568, 500);
  delay(500);

  tone(9, 1397, 400);
  delay(400);
  tone(9, 1480, 300);
  delay(300);
}

