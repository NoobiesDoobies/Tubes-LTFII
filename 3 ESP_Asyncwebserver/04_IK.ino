#include <SpeedTrig.h>

#define PI 3.1415

int arm1Offset = 0;
int arm2Offset = 0;

const float L1 = 10; //cm
const float L2 = 7;
const float GEAR_RATIO_1 = 2; // gear1 : gear2
const float GEAR_RATIO_2 = 3;
float x,y,z;
float arm1Angle, arm2Angle, endEffectorAngle;


void calculate_IK(float x, float y, float z){
  float h2 = x*x+y*y;
  arm2Angle = (180 - SpeedTrig.acos((L1*L1 + L2*L2 - h2)/(2*L1*L2)));
  float thetaP = SpeedTrig.atan2(x , y) * 180 / PI;
  float alpha = SpeedTrig.acos((L1*L1 + h2 - L2*L2)/(2*L1*sqrt(h2))) * 180 / PI;
  arm1Angle = thetaP - alpha;
  arm1Angle = arm1Angle * GEAR_RATIO_1;
  arm2Angle = arm2Angle * GEAR_RATIO_2;
//
//  endEffectorAngle = 0;
}
