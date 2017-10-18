/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin AO Trig to Arduino pin A1
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
Version 2 - added an if statement to output range when it changes
*/

#define trigPin A1
#define echoPin A0

int range = -1;
int previousRange = -1;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  
  if (distance >= 200 || distance <= 0){
    range = -1;
    if (range != previousRange){
      Serial.println("Out of range");
    }
  }
  else {
    if(distance <= 5){
      range = 5;
      if (range != previousRange){
        Serial.println("Too close");
      }
    }else if(distance <= 10){
      range = 10;
      if (range != previousRange){
        Serial.println("Perfect distance");
      }
    }else{
      range = 255;
      if (range != previousRange){
        Serial.println("Too far");
      }
    }
  }
  previousRange = range;
  delay(500);
}
