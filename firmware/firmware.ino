#include <AccelStepper.h>
#include <Servo.h>

const int PIN_STEPPER_STEP = 2;
const int PIN_STEPPER_DIRECTION = 3;
const int PIN_STEPPER_ENABLE = 6;
const long ACCELERATION = 1000;
AccelStepper stepper(AccelStepper::DRIVER, PIN_STEPPER_STEP, PIN_STEPPER_DIRECTION); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
int readByte = 0;
int nextDrink = 0;
int currentDrink = 0;
const long INITIAL_POSITION_OFFSET = -960;
const long MICRO_STEPS = 8;
long DrinkPositionFaktor = 20*MICRO_STEPS*15-32;
long targetPosition = 0;

boolean initialized = true;
boolean waitingForNewPosition = false;
boolean readyForNextCommand = false;

Servo tapServo;
int pos = 0;
int servoDirection = 1;

boolean isTapping = false;
const int buttonPin = 5;
int buttonState = 0;
boolean init_pos = false;
unsigned long lastButtonPress = 0;

void setup()
{  
   Serial.begin(115200);
   stepper.setEnablePin(PIN_STEPPER_ENABLE);
   stepper.setPinsInverted(false, false, true);
   stepper.setMaxSpeed(10000);
//   stepper.setSpeed(0);
   stepper.setCurrentPosition(0);
   stepper.setAcceleration(ACCELERATION);
   stepper.enableOutputs();
   
   tapServo.attach(4);
   tapServo.write(0);
   
   pinMode(buttonPin, INPUT);
}

void loop()
{
       buttonState = digitalRead(buttonPin);
       if (init_pos == false)
       {
           stepper.setSpeed(200*MICRO_STEPS);
           stepper.runSpeed();
           init_pos=false;
           if (buttonState == HIGH)
           {
               if(stepper.currentPosition() > 3000) 
               {
                 stepper.setCurrentPosition(INITIAL_POSITION_OFFSET);
                 stepper.moveTo(0);
                 targetPosition = 0;
                 init_pos=true;
                 waitingForNewPosition = true;
                 readyForNextCommand = false;
               }
           }
       }

    if(initialized) {
        if (Serial.available() > 0 && readyForNextCommand) {
                readByte = Serial.read();
                if(readByte == 't') {
                  isTapping = true;
                  readyForNextCommand = false;
                } else if(readByte == 'n') {
                  nextDrink = Serial.parseInt();
                  Serial.print("Moving to Drink: ");
                  Serial.println(nextDrink);
                  int drinkDeltaRight = (nextDrink - currentDrink + 10) % 10;
                  int drinkDeltaLeft = (nextDrink - currentDrink - 10) % 10;
                  long stepDelta = 0;
//                  if(abs(drinkDeltaRight) < abs(drinkDeltaLeft)) {
                    stepDelta = drinkDeltaRight * DrinkPositionFaktor;
//                  } else {
//                    stepDelta = drinkDeltaLeft * DrinkPositionFaktor;
//                  }
                  targetPosition += stepDelta;
                  Serial.print("Target position: ");
                  Serial.println(targetPosition);
//                  stepper.enableOutputs();
                  stepper.moveTo(targetPosition);
                  waitingForNewPosition = true;
                  readyForNextCommand = false;
                } else if(readByte == 'f') {
                  Serial.println("Mixing complete");
                } else if(readByte == 'c') {
                  Serial.print("My Current Position: ");
                  Serial.println(stepper.currentPosition()/DrinkPositionFaktor);
                } else if(readByte == 'i') {
//                  stepper.enableOutputs();
                  Serial.println("Searching 0 - Position... ");
                  stepper.setCurrentPosition(0);
                  init_pos=false;
                  readyForNextCommand = false;
                } else if(readByte == 'ms') {
                  long stepDelta = Serial.parseInt();
                  targetPosition += stepDelta;
                  Serial.print("Target position: ");
                  Serial.println(targetPosition);
//                  stepper.enableOutputs();
                  stepper.moveTo(targetPosition);
                  waitingForNewPosition = true;
                  readyForNextCommand = false;
                } else if(readByte == 's') {
                  int angle = Serial.parseInt();
                  tapServo.write(angle);
               }
          }
    } else {
         if( Serial.read() == '1') 
         if( Serial.read() == '0')
         if( Serial.read() == 's')
         if( Serial.read() == 'h')
         if( Serial.read() == 'o')
         if( Serial.read() == 'o')
         if( Serial.read() == 't')
         if( Serial.read() == 'e')
         if( Serial.read() == 'r') 
             initialized = true;
         
    }
     
          if(targetPosition == stepper.currentPosition() && waitingForNewPosition) {
            Serial.println("Drink reached");
            currentDrink = nextDrink;
            waitingForNewPosition = false;
            readyForNextCommand = true;
//            stepper.disableOutputs();
          }
          if(isTapping) {
            Serial.println("Start tapping");
            tapServo.write(180);              // tell servo to go to position in variable 'pos' 
            delay(4000);
            Serial.println("Stop tapping");
            tapServo.write(0);
            Serial.println("Waiting for refill");
            tapServo.write(0);
            delay(500);
            tapServo.write(90);
            delay(200);
            tapServo.write(130);
            delay(200);
            tapServo.write(90);
            delay(200);
            tapServo.write(50);
            delay(200);
            tapServo.write(90);
            delay(200);
            tapServo.write(80);
            delay(800);
            tapServo.write(60);
            delay(800);
            tapServo.write(80);
            delay(2000);
            tapServo.write(0);
            isTapping = false;
            readyForNextCommand = true;
          }
         stepper.run();
}
