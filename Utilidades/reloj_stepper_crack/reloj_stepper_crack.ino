
/*
 Stepper Motor Control - one revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.


 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);


boolean empece = false;
boolean orden = false;
boolean go_to_play = false;
unsigned long contador = 0;
void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(150);
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(12,INPUT);
  pinMode(6,INPUT);
  digitalWrite(6,HIGH);
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);  
 // delay(2000);
  Serial.println("AAAAAAAA"); 
  myStepper.step(4100); // DOS VUELTAS
}


void loop() {
  if ((millis() - contador) >= 144000) { // Esto lo puedes dejar como estaba, pero creo que es más ilustrativo así
    contador = millis();
    myStepper.step(82);
  }

  if(digitalRead(6)==0){myStepper.step(-1);}
}

