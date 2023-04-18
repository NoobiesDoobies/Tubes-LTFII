#include <AccelStepper.h>
#include <Servo.h>

#define SUDUT_MIN 0
#define SUDUT_MAX 180

#define STEPPER_SPEED 600

float arm1CurrentAngle = 0;
const float stepsPerRevolution = 2048;  // jumlah langkah per satu putaran penuh
const float revolution = 360; // 1 revolusi penuh 360 derajat
float step_angle = revolution / stepsPerRevolution;
int t_pwm;
int steps;

const int SERVO_PIN = 13; // pin for servo motor

const int ARM1_STEP_PIN = 16;
const int ARM1_DIR_PIN = 17;
const int ARM1_MS1_PIN = 4;
const int ARM1_MS2_PIN = 18;

const int ARM2_STEP_PIN = 19;
const int ARM2_DIR_PIN = 22;
const int ARM2_MS1_PIN = 21;
const int ARM2_MS2_PIN = 23;

Servo EndEffector;
//Stepper Arm1(stepsPerRevolution, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4);
AccelStepper Arm1(AccelStepper::FULL4WIRE, ARM1_STEP_PIN, ARM1_DIR_PIN, ARM1_MS1_PIN, ARM1_MS2_PIN);
AccelStepper Arm2(AccelStepper::FULL4WIRE, ARM2_STEP_PIN, ARM2_DIR_PIN, ARM2_MS1_PIN, ARM2_MS2_PIN);



void initActuator(){
  // set servo pin as output
  pinMode(SERVO_PIN, OUTPUT);
  // attach servo to pin
  EndEffector.attach(SERVO_PIN);
//  Arm1.setSpeed(15);

  Arm1.setMaxSpeed(STEPPER_SPEED);
  Arm1.setAcceleration(STEPPER_SPEED);
  Arm2.setMaxSpeed(STEPPER_SPEED);
  Arm2.setAcceleration(STEPPER_SPEED);
  
  // Set the initial position of the stepper motor to 0
  Arm1.setCurrentPosition(0);
  Arm2.setCurrentPosition(0);

  Serial.println("Servo and Stepper is ready");
}

//void step_Degree(double angle){ 
//  float koreksi = 1; // ubah angka koreksi ini jika pergerakan motor stepper tidak sesuai dengan besar sudut yang diperintahkan
//  steps = (int)(angle / step_angle * koreksi);
//  Serial.print("\tSteps: ");
//  Serial.println(steps);
//   stepper.step(steps);
//}

//void rotateBasedOnAngle(int pinServo, double angle) {
//  // Fungsi Konversi sudut ke t_pwm
//    t_pwm = (int) (500 + 200*angle/19) ; // Lengkapi Fungsi Konversi sudut ke t_pwm
//    
//    digitalWrite(pinServo, HIGH);
//    delayMicroseconds(t_pwm);
//    digitalWrite(pinServo, LOW);
//    delay(50);
//}

void moveActuator(){
//  Serial.print("Moving Actuator to: ");
  
  //move all actuator to the desired angle
//  Serial.print("End Effector: " + String(endEffectorAngle));
  EndEffector.write(endEffectorAngle);
//  float deltaArm1 = arm1Angle - arm1CurrentAngle;
  int arm1Step = map(arm1Angle+180, 0, 360, 0, stepsPerRevolution);
//   if(arm1CurrentAngle != arm1Angle){
//     Serial.println("Setting MOVETO");
//     Arm1.moveTo(arm1Angle + arm1Offset);
// //    Arm1.run(); 
//     arm1CurrentAngle = arm1Angle;
//   }
  Arm1.moveTo(arm1Angle + arm1Offset);
  Arm2.moveTo(arm2Angle + arm2Offset);
//  Serial.println("End Effector: " + String(endEffectorAngle) + "\tArm1: " + String(arm1Angle));
//  Serial.println("Speed1: " + String(Arm1.speed()) + "\tPos1: " + String(Arm1.currentPosition()) + "\tTarget1: " + String(arm1Step) + "Offset: " + String(arm1Offset));

  /* Stepper.h library */
//  Arm1.step(arm1Pos);

  /* AccelStepper.h library */
  // not blocking but bad
  Arm1.run(); 
  Arm2.run();
  
  
  // blocking but very smooth
  // Arm1.runToNewPosition(arm1Step);
  

}
