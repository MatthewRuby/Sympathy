#include <Servo.h>

Servo theServo;
int servoPos = 0;

int MAX = 110;
int MIN = 65;

int DIST = 45;

int DIR = 0;

boolean bCLOSEENOUGH = false;

int sensorPin = A0;
int sensorValue = 0;
int prevValue = 0;

void setup() {
  Serial.begin(9600);
  
  theServo.attach(9);  
  theServo.write(MIN);
  DIR = 1;
  
}

void loop() {
  
  sensorValue = 0.1 * analogRead(sensorPin) + ( 1 - 0.1) * prevValue;   

  if(sensorValue < DIST){
    
    bCLOSEENOUGH = true;

    if(DIR == 1){
      
// --- Close ---
      servoPos++;
      
    } else if (DIR == 2){
      
// --- Open ---
      servoPos--;
    }
    
    theServo.write(servoPos);
  
  } else {
    
    bCLOSEENOUGH = false;
    
    servoPos = MAX;
    theServo.write(servoPos);
    
  }
  
  Serial.println(servoPos);
  
  if(servoPos < MIN){
    servoPos = MIN;
    DIR = 1;
  } else if(servoPos > MAX){
    servoPos = MAX;
    DIR = 2;
  }

  prevValue = sensorValue;
}
