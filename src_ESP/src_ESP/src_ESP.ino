#include "BluetoothSerial.h"
#include <TFScope22.h>
#include <Stepper.h>


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
String deviceName = "qwer";

#define BAUD 500000
#define SUDUT_MIN 0
#define SUDUT_MAX 180
#include <TFScope22.h>

// Pin drive motor ULN2003
#define IN1 DO0
#define IN2 DO1
#define IN3 DO2
#define IN4 DO3

// const float stepsPerRevolution = 2048;  // jumlah langkah per satu putaran penuh
// const float revolution = 360; // 1 revolusi penuh 360 derajat
// float step_angle = revolution / stepsPerRevolution;
// int servo = AO0;
// double sudutServo = 0;
// double sudutStepper = 0;
// int t_pwm;
// float steps;

float x = 0.0, y = 0.0;


// Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

// void step_Degree(double angle){ 
//   float koreksi = 1; // ubah angka koreksi ini jika pergerakan motor stepper tidak sesuai dengan besar sudut yang diperintahkan
//   steps = (int)(angle / step_angle * koreksi);
//   Serial.print("\tSteps: ");
//   Serial.println(steps);
//   myStepper.step(steps);
// }

// void rotateBasedOnAngle(double angle) {
//   // Fungsi Konversi sudut ke t_pwm
//     t_pwm = (int) (500 + 200*angle/19) ; // Lengkapi Fungsi Konversi sudut ke t_pwm
    
//     dacWrite(servo, 255);
//     delayMicroseconds(t_pwm);
//     dacWrite(servo, 0);
//     delay(50);
//   }



void setup() {
  Serial.begin(BAUD);
  // myStepper.setSpeed(5); 
  SerialBT.begin(deviceName); 
  Serial.println("");
  Serial.println("The device started, now you can pair it with bluetooth!");
  // pinMode(servo, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    String positionString = SerialBT.readString();
    Serial.println(positionString);

    int indexEnter = positionString.indexOf('\n');
    String subString = positionString.substring(indexEnter+1, positionString.length());
    if(indexEnter != -1){
      while(subString.substring(indexEnter+1, subString.length()).indexOf('\n') != -1){
        subString = subString.substring(indexEnter+1, subString.length());
        indexEnter = subString.indexOf('\n');
      }
      int index = subString.indexOf(' ');
      x = subString.substring(0,index).toFloat();
      y = subString.substring(index+1, subString.length()-1).toFloat();
    }
    else{
      int index = positionString.indexOf(' ');
      x = positionString.substring(0,index).toFloat();
      y = positionString.substring(index+1, positionString.length()).toFloat();
    }
    
  }
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("\ty: ");
  Serial.println(y);

  // rotateBasedOnAngle(sudutServo);
  delay(20);
}
