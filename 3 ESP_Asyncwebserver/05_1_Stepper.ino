#include <AccelStepper.h>
#define SUDUT_MIN 0
#define SUDUT_MAX 180

#define STEPPER1_SPEED 100
#define STEPPER2_SPEED 100

#define CHANGE_DIRECTION_COUNTER_STEP 10

float arm1CurrentAngle = 0;
const float stepsPerRevolution = 2048;  // jumlah langkah per satu putaran penuh
const float revolution = 360; // 1 revolusi penuh 360 derajat
float step_angle = revolution / stepsPerRevolution;
int t_pwm;
int steps;



const int ARM1_STEP_PIN = 19;
const int ARM1_DIR_PIN = 22;
const int ARM1_MS1_PIN = 21;
const int ARM1_MS2_PIN = 23;

//const int STEP_PIN2 = 19;
//const int DIR_PIN2 = 22;
//const int MS1_PIN2 = 21;
//const int MS2_PIN2 = 23;

const int ARM2_STEP_PIN = 33;
const int ARM2_DIR_PIN = 26;
const int ARM2_MS1_PIN = 25;
const int ARM2_MS2_PIN = 27;

//Stepper Arm1(stepsPerRevolution, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4);
AccelStepper Arm1(AccelStepper::FULL4WIRE, ARM1_STEP_PIN, ARM1_DIR_PIN, ARM1_MS1_PIN, ARM1_MS2_PIN);
AccelStepper Arm2(AccelStepper::FULL4WIRE, ARM2_STEP_PIN, ARM2_DIR_PIN, ARM2_MS1_PIN, ARM2_MS2_PIN);



void initStepper(){

//  Arm1.setSpeed(15);

  Arm1.setMaxSpeed(STEPPER1_SPEED);
  Arm1.setAcceleration(STEPPER1_SPEED*2);
  Arm2.setMaxSpeed(STEPPER2_SPEED);
  Arm2.setAcceleration(STEPPER2_SPEED*2);
  
  // Set the initial position of the stepper motor to 0
  Arm1.setCurrentPosition(0);
  Arm2.setCurrentPosition(0);

  Serial.println("Stepper is ready");
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

void moveStepper(){
  // Move all Stepper to the desired angle
  int arm1Step = map(arm1Angle+arm1Offset, 0, 360, 0, stepsPerRevolution);
  int arm2Step = map(arm2Angle+arm2Offset, 0, 360, 0, stepsPerRevolution);
//  Serial.println("offset: " + String(arm1Offset) + "\tstep: " + String(arm1Step) + "\tangle: " + String(arm1Angle));
  Arm1.moveTo(arm1Step);
  Arm2.moveTo(arm2Step);


  /* AccelStepper.h library */
  Arm1.run(); 
  Arm2.run();
  
}
