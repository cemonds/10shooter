// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>
#include <Servo.h>


AccelStepper stepper(AccelStepper::DRIVER, 2, 3); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
int incomingInt = 0;
int DrinkPositionFaktor = 20*16*5;
int targetPosition = 0;
boolean waitingForNewPosition = false;

Servo tapServo;
int pos = 0;
int servoDirection = 1;

boolean isTapping = false;

const int buttonPin = 5;
int buttonState = 0;
boolean init_pos = false;


void setup()
{  
   Serial.begin(115200);
   stepper.setMaxSpeed(500);
//   stepper.setSpeed(0);
   stepper.setCurrentPosition(0);
   stepper.setAcceleration(50);
   
   tapServo.attach(4);
   tapServo.write(0);
   
   pinMode(buttonPin, INPUT);
}

void loop()
{
       if (init_pos == false){
             buttonState = digitalRead(buttonPin);
             if (buttonState == HIGH){
                 stepper.setSpeed(0);
                 stepper.runSpeed();
                 stepper.setCurrentPosition(0);
                 init_pos=true;
             }else{
//                 stepper.moveTo(stepper.currentPosition()+1);
                 stepper.setSpeed(200);
                 stepper.runSpeed();
                 init_pos=false;
             }    
       } 





        if (Serial.available() > 0) {
                incomingInt = Serial.read();
                if(incomingInt == 't') {
                  isTapping = true;
                } else if(incomingInt == 'n') {
                  int position = Serial.parseInt();
                  Serial.print("Moving to Drink: ");
                  Serial.println(position);
                  targetPosition = position * DrinkPositionFaktor;
                  stepper.moveTo(targetPosition);
                  waitingForNewPosition = true;
                } else if(incomingInt == 'c') {
                  Serial.print("My Current Position: ");
                  Serial.println(stepper.currentPosition()/DrinkPositionFaktor);
                }else if(incomingInt == 'i'){
                  Serial.println("Searching 0 - Position... ");
                  init_pos=false;
               }
          }
          if(targetPosition == stepper.currentPosition() && waitingForNewPosition) {
            Serial.println("Drink reached");
            waitingForNewPosition = false;
          }
          if(isTapping) {
            Serial.println("Start tapping");
            tapServo.write(180);              // tell servo to go to position in variable 'pos' 
            delay(5000);
            Serial.println("Stop tapping");
            tapServo.write(0);
            isTapping = false;
          }
         stepper.run();
}
