#include <Servo.h>

// Create a servo object
Servo servo1;
Servo servo2;

int angle1 = 0;
int angle2 = 10;

// 0: 20 180
// 0 -> 150 180, 150 150 
// 1: 180 150
// 2: 180 20
// 2 -> 1: 180 150, 150 150, 150 180


// 20 180 -> 150 180 -> 150 150 -> 180 150 -> 180 20 -> 180 150 -> 150 150 -> 150 180 -> 20 180

enum{DOWN, MIDDLE, UP};
int endEffectorState = DOWN;
int z = 0;
void setup() {
 Serial.begin(115200);
 // Attach the servo to pin 13
 servo1.attach(14);
 servo2.attach(13);
}

void loop() {
 Serial.read();
 while(!Serial.available()){
//    Serial.println("z: " + String(z)+ "State: " + String(endEffectorState));
 switch(endEffectorState){
     case DOWN:
       servo1.write(20);
       servo2.write(180);
//        Serial.println("20 180");
       if(z == 1){
         endEffectorState = MIDDLE;
         servo1.write(150);
         servo2.write(180);
//          Serial.println("150 180");
         servo1.write(150);
         servo2.write(150);
//          Serial.println("150 150");
         Serial.println("DOWN TO MID");
       }
       break;
     case UP:
       
       servo2.write(20);
//        Serial.println("180 20");
       servo1.write(150);
       if(z == 1){
         endEffectorState = MIDDLE;
         servo1.write(180);
         servo2.write(150);
//          Serial.println("180 150");
//          Serial.println("150 150");
         Serial.println("UP TO MID");
       }
       break;
     case MIDDLE:
       if(z == 0){
         endEffectorState = DOWN;
         servo1.write(150);
         servo2.write(180);
//          Serial.println("150 180");
         Serial.println("MID TO DOWN");
       }
       if(z == 2){
         endEffectorState = UP;
         servo1.write(150);
         servo2.write(150);
//          Serial.println("180 150");
         Serial.println("MID TO UP");
       }
       break;
   }
   }
 
 z = Serial.parseInt();
 

//  angle1 = Serial.parseInt();
//  angle2 = Serial.parseInt();
//  Serial.println("Angle1: " + String(angle1) + "\tAngle2: " + String(angle2));
 Serial.println("z: " + String(z));
}


// ================================================================

// #include <Servo.h>

// // Create a servo object
// Servo servo1;
// Servo servo2;
// int delays = 0;


// #include <AccelStepper.h>
// #include <Servo.h>

// // Define the number of steps per revolution
// const int STEPS_PER_REVOLUTION = 2048;

// // Define the stepper motor pins
// const int STEP_PIN = 19;
// const int DIR_PIN = 22;
// const int MS1_PIN = 21;
// const int MS2_PIN = 23;

// //const int STEP_PIN2 = 19;
// //const int DIR_PIN2 = 22;
// //const int MS1_PIN2 = 21;
// //const int MS2_PIN2 = 23;

// const int STEP_PIN3 = 33;
// const int DIR_PIN3 = 26;
// const int MS1_PIN3 = 25;
// const int MS2_PIN3 = 27;

// int angle = 0;
// int angle2 = 0;

// // Initialize the stepper motor object
// AccelStepper stepper(AccelStepper::FULL4WIRE, STEP_PIN, DIR_PIN, MS1_PIN, MS2_PIN);
// //AccelStepper stepper2(AccelStepper::FULL4WIRE, STEP_PIN2, DIR_PIN2, MS1_PIN2, MS2_PIN2);
// AccelStepper stepper3(AccelStepper::FULL4WIRE, STEP_PIN3, DIR_PIN3, MS1_PIN3, MS2_PIN3);
// int timer = 0;  
// long steps = 0;
// void setup() {
//   Serial.begin(115200);
//   // Attach the servo to pin 13
//   servo1.attach(14);
//   servo2.attach(13);
//   // Set the motor speed
//   Serial.println("Speed: Angle: ");
//   // stepper.setSpeed(5); // Set the speed to 20 RPM
//   while(!Serial.available()){}
//   int SPEED = Serial.parseInt();
//   // 400 11
//   // 600 10905
//   // 1000 10810
//   // 2000 10756
//   // 10000 10734
//   //
//   angle = Serial.parseInt();
//   Serial.read();
//   stepper.setMaxSpeed(SPEED);
//   stepper.setAcceleration(SPEED);
// //  stepper2.setMaxSpeed(SPEED);
// //  stepper2.setAcceleration(SPEED);
//   stepper3.setMaxSpeed(SPEED);
//   stepper3.setAcceleration(SPEED);
//   // Set the initial position of the stepper motor to 0
//   stepper.setCurrentPosition(0);
// //  stepper2.setCurrentPosition(0);
//   stepper3.setCurrentPosition(0);
//   steps = angle * STEPS_PER_REVOLUTION / 360 * 2;


  
//  stepper.moveTo(steps);
// //  stepper2.moveTo(steps);
//   stepper3.moveTo(steps);
//   timer = millis();


  
// }

// void loop() {
//   if (stepper.distanceToGo() == 0) {
    
//   }
//   else{
//         Serial.println("Position: " + String(stepper.currentPosition()) + "\tSpeed: " + String(stepper.speed()) + "\tTarget: " + String(steps) + "\tTotal time = " + String(millis()-timer) + "\tangle2: " + String(angle2) + "\tdelay: " + String(delays));
//   }

//   if(Serial.available()){
//     angle2 = Serial.parseInt();
//     delays = Serial.parseInt();
    
//     stepper.stop();
//     stepper3.stop();
//     servo1.write(angle2);
//     servo2.write(angle2);
    
//     delay(delays);
//     Serial.read();
//     Serial.println("angle2: " + String(angle2) + "delay: " + String(delays));
//   }



//    stepper.run();
// //  stepper2.run();
//   stepper3.run();
// }
