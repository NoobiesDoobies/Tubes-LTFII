#include <Servo.h>

// Create a servo object
Servo servo1;
Servo servo2;

int angle1 = 0;
int angle2 = 10;

// MAX TURUN: 150 30
// 

void setup() {
  Serial.begin(115200);
  // Attach the servo to pin 13
  servo1.attach(14);
  servo2.attach(13);
}

void loop() {
  Serial.read();
  while(!Serial.available()){
    
    servo1.write(angle1);
    servo2.write(angle2);
  }

  angle1 = Serial.parseInt();
  angle2 = Serial.parseInt();
  Serial.println("Angle1: " + String(angle1) + "\tAngle2: " + String(angle2));
}


//
//#include <AccelStepper.h>
//#include <Servo.h>
//
//// Define the number of steps per revolution
//const int STEPS_PER_REVOLUTION = 2048;
//
//// Define the stepper motor pins
//const int STEP_PIN = 16;
//const int DIR_PIN = 17;
//const int MS1_PIN = 4;
//const int MS2_PIN = 18;
//
//const int STEP_PIN2 = 19;
//const int DIR_PIN2 = 22;
//const int MS1_PIN2 = 21;
//const int MS2_PIN2 = 23;
//
//Servo servo;
//const int servoPin = 13;
//int angle = 0;
//
//// Initialize the stepper motor object
//AccelStepper stepper(AccelStepper::FULL4WIRE, STEP_PIN, DIR_PIN, MS1_PIN, MS2_PIN);
//AccelStepper stepper2(AccelStepper::FULL4WIRE, STEP_PIN2, DIR_PIN2, MS1_PIN2, MS2_PIN2);
//int timer = 0;
//long steps = 0;
//void setup() {
//  Serial.begin(115200);
//  pinMode(servoPin, OUTPUT);
//  // Set the motor speed
//  Serial.println("Speed: Angle: ");
//  // stepper.setSpeed(5); // Set the speed to 20 RPM
//  while(!Serial.available()){}
//  int SPEED = Serial.parseInt();
//  // 400 11
//  // 600 10905
//  // 1000 10810
//  // 2000 10756
//  // 10000 10734
//  //
//  angle = Serial.parseInt();
//
//  
//  stepper.setMaxSpeed(SPEED);
//  stepper.setAcceleration(SPEED);
//  stepper2.setMaxSpeed(SPEED);
//  stepper2.setAcceleration(SPEED);
//  // Set the initial position of the stepper motor to 0
//  stepper.setCurrentPosition(0);
//  stepper2.setCurrentPosition(0);
//  steps = angle * STEPS_PER_REVOLUTION / 360 * 2;
//
//
//  
//  servo.attach(servoPin);
//  // stepper.moveTo(steps);
//  stepper2.moveTo(steps);
//  timer = millis();
//}
//
//void loop() {
//  if (stepper.distanceToGo() == 0) {
//    
//  }
//  else{
//        Serial.println("Position: " + String(stepper.currentPosition()) + "\tSpeed: " + String(stepper.speed()) + "\tTarget: " + String(steps) + "\tTotal time = " + String(millis()-timer));
//  }
//  // stepper.run();
//  stepper2.run();
//  servo.write(angle);
//
//  
//}
