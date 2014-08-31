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

const int PIN_STEPPER_STEP = 2;
const int PIN_STEPPER_DIRECTION = 3;
const int PIN_STEPPER_ENABLE = 6;
AccelStepper stepper(AccelStepper::DRIVER, PIN_STEPPER_STEP, PIN_STEPPER_DIRECTION); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
int incomingInt = 0;
int DrinkPositionFaktor = 20*16*5;
int targetPosition = 0;
boolean waitingForNewPosition = false;
boolean readyForNextCommand = false;

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
   stepper.setEnablePin(PIN_STEPPER_ENABLE);
   stepper.setPinsInverted(false, false, true);
   stepper.setMaxSpeed(10000);
//   stepper.setSpeed(0);
   stepper.setCurrentPosition(0);
   stepper.setAcceleration(500);
   stepper.enableOutputs();
   
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
                 readyForNextCommand = true;
                 stepper.disableOutputs();
             }else{
                 stepper.setSpeed(1000);
                 stepper.runSpeed();
                 init_pos=false;
             }    
       } 





        if (Serial.available() > 0 && readyForNextCommand) {
                incomingInt = Serial.read();
                if(incomingInt == 't') {
                  isTapping = true;
                  readyForNextCommand = false;
                } else if(incomingInt == 'n') {
                  int position = Serial.parseInt();
                  Serial.print("Moving to Drink: ");
                  Serial.println(position);
                  targetPosition = position * DrinkPositionFaktor;
                  stepper.enableOutputs();
                  stepper.moveTo(targetPosition);
                  waitingForNewPosition = true;
                  readyForNextCommand = false;
                } else if(incomingInt == 'c') {
                  Serial.print("My Current Position: ");
                  Serial.println(stepper.currentPosition()/DrinkPositionFaktor);
                }else if(incomingInt == 'i'){
                  stepper.enableOutputs();
                  Serial.println("Searching 0 - Position... ");
                  init_pos=false;
                  readyForNextCommand = false;
               }
          }
          if(targetPosition == stepper.currentPosition() && waitingForNewPosition) {
            Serial.println("Drink reached");
            waitingForNewPosition = false;
            readyForNextCommand = true;
            stepper.disableOutputs();
          }
          if(isTapping) {
            Serial.println("Start tapping");
            tapServo.write(180);              // tell servo to go to position in variable 'pos' 
            delay(4000);
            Serial.println("Stop tapping");
            tapServo.write(0);
            Serial.println("Waiting for refill");
            delay(4000);
            isTapping = false;
            readyForNextCommand = true;
          }
         stepper.run();
}
