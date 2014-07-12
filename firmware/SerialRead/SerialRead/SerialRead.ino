// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::DRIVER, 2, 3); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
int incomingInt = 0;
void setup()
{  
   Serial.begin(115200);
   stepper.setMaxSpeed(200);
//   stepper.setSpeed(0);
   stepper.setCurrentPosition(0);
   stepper.setAcceleration(10);
   
}

void loop()
{
          if (Serial.available() > 0) {
                Serial.print("My Current Position: ");
                Serial.println(stepper.currentPosition());
                incomingInt = Serial.parseInt();
                Serial.print("Moving to: ");
                Serial.println(incomingInt);
                stepper.moveTo(incomingInt);
          }
         stepper.run();
}
