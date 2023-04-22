#include <SpeedTrig.h>

#define PI 3.1415

int arm1Offset = 0;
int arm2Offset = 0;

const float L1 = 20; //cm
const float L2 = 20;
const float GEAR_RATIO_1 = 2; // gear1 : gear2
const float GEAR_RATIO_2 = 2;
float x = 0,y = 40,z = 0;
float arm1Angle, arm2Angle, endEffectorAngle;

float wrap_around(float angle){
   angle = fmod(angle, 360);
   if(angle >= 180){
      angle = -(360-angle);
   }
   return angle;
}

void calculate_IK(float x, float y, float z){
  float h2 = x*x+y*y;
  arm2Angle = (180 - acos((L1*L1 + L2*L2 - h2)/(2*L1*L2)) * 180 / PI);
  float thetaP = atan2(x, y) * 180 / PI;
  float alpha = acos((L1*L1 + h2 - L2*L2)/(2*L1*sqrt(h2))) * 180 / PI;
  arm1Angle = thetaP - alpha;
//  arm1Angle = arm1Angle * GEAR_RATIO_1;
//  arm2Angle = arm2Angle * GEAR_RATIO_2;

  
//  Serial.print("x: " + String(x) + "\ty: " + String(y) + "\tAngle1: " + String(arm1Angle) + "\tAngle2: " + String(arm2Angle));
  // Wrap around 
  arm1Angle = wrap_around(arm1Angle);
  arm2Angle = wrap_around(arm2Angle);
  
  // Set constrain
  arm1Angle = constrain(arm1Angle, -90, 90);
  arm2Angle = constrain(arm2Angle, -170, 170);
//  Serial.println("\tAngle1: " + String(arm1Angle) + "\tAngle2: " + String(arm2Angle));

  
  
//  endEffectorAngle = 0;
}
