#include <Servo.h>

const int buttonPin = 2; 
const int pingPin = 7;
Servo leftMotor;
Servo rightMotor;
int servoState =0;
long cm = 0;

boolean currentState = LOW;//stroage for current button state
boolean lastState = LOW;//storage for last button state


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  leftMotor.attach(13);
  rightMotor.attach(12);
  pinMode(buttonPin, INPUT);
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);
  moveBot();
  makeTurn(cm);
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void moveBot(){
  currentState = digitalRead(buttonPin);
       
  if(currentState == HIGH && lastState == LOW) {
    
    Serial.println("pressed");
    delay(5);
    if (servoState==1){
      leftMotor.write(90);
      rightMotor.write(90);
      servoState=0;
    }
    
    else{
      leftMotor.write(0);
      rightMotor.write(180);
      servoState = 1;
    }
  }
//  else if(currentState == LOW && lastState == HIGH){
//    Serial.println("released");
//    delay(5);
//    if()
//    leftMotor.write(90);
//    rightMotor.write(90);
//    delay(10);
//  }
  lastState = currentState;
}

void makeTurn(long distance){
  if(servoState==1){
    if (distance <= 5){
//      leftMotor.write(180);
//      rightMotor.write(180);
      leftMotor.write(90);
      rightMotor.write(90);
      delay(80);
      leftMotor.write(180);
      rightMotor.write(90);
    }
  
    else{
      leftMotor.write(0);
      rightMotor.write(180);
    }
  
  
  }
//  if (distance <= 5){
//    leftMotor.write(90);
//    rightMotor.write(90);
//    delay(80);
//    leftMotor.write(180);
//    rightMotor.write(90);
//  }
//  
//  else{
//     leftMotor.write(0);
//      rightMotor.write(180);
//  }
}
