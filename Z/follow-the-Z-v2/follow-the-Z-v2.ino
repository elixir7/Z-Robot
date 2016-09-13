#include <Servo.h>

Servo servoRight;
Servo servoLeft;

void setup() {
  servoLeft.attach(11);
  servoRight.attach(10);

 
  pinMode(9, OUTPUT); //Speaker
  pinMode(8, OUTPUT); //Left LED
  pinMode(2, OUTPUT); //Right LED
  Serial.begin(9600);

  int numberOfNotes = 12;
  int notes[] = {1568, 1568, 1568, 1568, 1865, 2093, 1568, 1568, 1568, 1568, 1397, 1480};
  int tempo[] = {500, 500, 500, 500, 300, 300, 500, 500, 500, 500, 300, 300};

  tone(9, 3000, 1000);
  delay(2000);

  forward(4);
  turn("right", 50);
  forward(35);
  turn("left", 100);
  forward(15);

  maneuver(1300, 1300, 1000);
  
  play(notes, tempo, numberOfNotes);

  forward(4);
  turn("right", 50);
  forward(35);
  turn("left", 100);
  forward(15);
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

void turn(String direction, int turn){
  int turnR = 0;
  if(direction == "right"){
    for(int moment = 0; moment <= turn; moment += 1){
      if (turnR != 100){
        turnR += 3;
      }
      //Serial.print(speed);
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1390 + turnR);
      delay(40);
    }
  }
  else if(direction == "left"){
    for(int moment = 0; moment <= turn; moment += 1){
      Serial.print(turnR);
      if (turnR != 200){
        turnR += 5;
      }
      servoLeft.writeMicroseconds(1700 - turnR);
      servoRight.writeMicroseconds(1390);
      delay(20);
    }
  }
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  turnR = 0;
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

void play(int notes[], int tempo[], int numb){
  for(int i = 0; i < numb; i++){
    Serial.print(notes[i]);
    tone(9, notes[i], tempo[i]);
    delay(tempo[i]); 
  }
}

