// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!
//McTavish - Oct 26, 2017
//use ultrasonic sensor - if path is clear, run motor.  Stop when too close.

//Need the adafruit library
#include <AFMotor.h>

//Ultrasonic sensor
#define trigPin A1
#define echoPin A0

//Keep track of range to object
int range = -1;
int previousRange = -1;

//Motor 1 is wired up, add line for motor 2 later
AF_DCMotor motor(1);


//Setup function - fun once and set variables
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");//troubleshooting
  pinMode(trigPin, OUTPUT);//ultrasonic setup
  pinMode(echoPin, INPUT);//ultrasonic setup
}

//Loop method
void loop() {
  
  //Get ultrasonic values
    long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  
  //When out of range assume path is clear, run motor
  if (distance >= 200 || distance <= 0){
    range = -1;
    if (range != previousRange){
      Serial.println("Out of range");
          motor.run(FORWARD);
          motor.setSpeed(255);
    }
  }
  //ultrasonic detects object
  else {
    //check if 10cm or less
    if(distance <= 10){
      range = 5;
      if (range != previousRange){
        Serial.println("Too close");
        motor.setSpeed(0);
        motor.run(RELEASE);
      }
      //greater than 10cm so run motor
    }else {
      range = 10;
      if (range != previousRange){
        Serial.println("perfect");
          motor.run(FORWARD);
          motor.setSpeed(255);
      }
    }
  }
  //reset previousrange
previousRange = range;
}
