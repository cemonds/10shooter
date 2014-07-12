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
   stepper.setMaxSpeed(100);
}

void loop()
{  
  static int counter = 0;
  if(++counter == 100) {
    stepper.move(10);
    counter = 0;
  }
//  stepper.moveTo(1000);
  stepper.setSpeed(200);	
  stepper.runSpeed();
//  if (stepper.distanceToGo() == 0)
//  {
    // Random change to speed, position and acceleration
    // Make sure we dont get 0 speed or accelerations
//    delay(1000);
//    stepper.moveTo(rand() % 200);
//    stepper.setMaxSpeed((rand() % 200) + 1);
//    stepper.setAcceleration((rand() % 200) + 1);
//  }
//  stepper.run();
}
