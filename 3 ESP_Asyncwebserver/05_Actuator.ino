#include <TFScope22.h>
#include <Stepper.h>

const float stepsPerRevolution = 2048;  // jumlah langkah per satu putaran penuh
const float revolution = 360; // 1 revolusi penuh 360 derajat
float step_angle = revolution / stepsPerRevolution;
int t_pwm;
int steps;

#define SUDUT_MIN 0
#define SUDUT_MAX 180
void step_Degree(double angle){ 
  float koreksi = 1; // ubah angka koreksi ini jika pergerakan motor stepper tidak sesuai dengan besar sudut yang diperintahkan
  steps = (int)(angle / step_angle * koreksi);
  Serial.print("\tSteps: ");
  Serial.println(steps);
  // stepper.step(steps);
}

void rotateBasedOnAngle(int pinServo, double angle) {
  // Fungsi Konversi sudut ke t_pwm
    t_pwm = (int) (500 + 200*angle/19) ; // Lengkapi Fungsi Konversi sudut ke t_pwm
    
    digitalWrite(pinServo, HIGH);
    delayMicroseconds(t_pwm);
    digitalWrite(pinServo, LOW);
    delay(50);
}

void moveActuator(){
  //move all actuator to the desired angle
}