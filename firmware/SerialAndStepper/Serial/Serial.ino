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

void setup()
{  
   Serial.begin(115200);
   stepper.setMaxSpeed(200);
   stepper.setSpeed(200);
   stepper.setCurrentPosition(0);
   stepper.setAcceleration(1);
}

void loop()
{  
  // send data only when you receive data:
  static int counter = 0;
  if(counter++ == 1000) {
    Serial.print("Current position ");
    Serial.println(stepper.currentPosition());
    Serial.print("target position ");
    Serial.println(stepper.targetPosition());
    counter = 0;
  }
  if (Serial.available() > 0) {
      // read the incoming byte:
      byte incomingByte = Serial.read();

      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte, DEC);
      stepper.moveTo((incomingByte - 'a') * 20);
//      stepper.runToNewPosition((incomingByte - 'a') * 20);
   }
   stepper.run();
}
