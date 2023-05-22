#define PI 3.141593

int arm1Offset = 0;
int arm2Offset = 0;

const float L1 = 13.2; //cm
const float L2 = 10.5;
const float L12 = L1*L1;
const float L22 = L2*L2;
const float L122 = (L1+L2) * (L1+L2);
const float GEAR_RATIO_1 = 2; // gear1 : gear2
const float GEAR_RATIO_2 = 1
;
float x = 0,y = L1+L2;
const float xDefault = 0;
const float yDefault = L1+L2;

float arm1Angle, arm2Angle;

float wrap_around(float angle){
   angle = fmod(angle, 360);
   if(angle >= 180){
      angle = -(360-angle);
   }
   return angle;
}

float radToDeg(float rad){
  return rad/PI * 180.0;
}

void calculate_IK(float x, float y, float z){
  float h2 = x*x+y*y;
  Serial.print("h2:" + String(h2) + "\t");

  if((h2 > L122)){
    Serial.println("ISNAN");
    return;
  }

  arm2Angle = -acos((h2 - L12 - L22)/(2*L1*L2));
  
  if(x > 0){
    arm1Angle = atan2(y,x) + atan2(L2*sin(arm2Angle),(L1+L2*cos(arm2Angle)));
  }
  else{
    Serial.print("X NEGATIF\t");
    arm1Angle = atan2(y,x) + atan2(L2*sin(arm2Angle),(L1+L2*cos(arm2Angle)));
  }
  arm1Angle = PI/2 - arm1Angle;

  // radToDeg
  arm1Angle = radToDeg(arm1Angle);
  arm2Angle = radToDeg(arm2Angle);
  // Set constrain
  arm1Angle = constrain(arm1Angle, -45, 180);
  arm2Angle = constrain(arm2Angle, -170, 170);
  
  Serial.println("x: " + String(x) + "\ty: " + String(y) + "\tAngle1: " + String(arm1Angle) + "\tAngle2: " + String(arm2Angle));
  arm1Angle = arm1Angle * GEAR_RATIO_1;
  arm2Angle = arm2Angle * GEAR_RATIO_2;
  // Wrap around 
//  arm1Angle = wrap_around(arm1Angle);
//  arm2Angle = wrap_around(arm2Angle);
  



  
  
//  endEffectorAngle = 0;
}
