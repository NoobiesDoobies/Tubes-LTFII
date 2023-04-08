#include <TFScope22.h>
#include <Stepper.h>
#include <Servo.h>

#define SUDUT_MIN 0
#define SUDUT_MAX 180

float arm1CurrentAngle = 0;
const float stepsPerRevolution = 2048;  // jumlah langkah per satu putaran penuh
const float revolution = 360; // 1 revolusi penuh 360 derajat
float step_angle = revolution / stepsPerRevolution;
int t_pwm;
int steps;

const int SERVO_PIN = AO0; // pin for servo motor
const int STEPPER_PIN_1 = DO0; // pin for stepper motor
const int STEPPER_PIN_2 = DO1;
const int STEPPER_PIN_3 = DO2;
const int STEPPER_PIN_4 = DO3;

Servo EndEffector;
Stepper Arm1(stepsPerRevolution, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4);


void initActuator(){
  // set servo pin as output
  pinMode(SERVO_PIN, OUTPUT);
  // attach servo to pin
  EndEffector.attach(SERVO_PIN);
  Arm1.setSpeed(15);
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
  Serial.print("Moving Actuator to: ");
  Serial.println("End Effector: " + String(endEffectorAngle));
  //move all actuator to the desired angle
  EndEffector.write(endEffectorAngle);
  float deltaArm1 = arm1Angle - arm1CurrentAngle;
  int arm1Pos = map(deltaArm1, 0, 180, 0, stepsPerRevolution);
  Arm1.step(arm1Pos);
  arm1CurrentAngle = arm1Angle; 
}
