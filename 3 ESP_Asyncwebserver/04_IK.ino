#define PI 3.141593

int arm1Offset = 0;
int arm2Offset = 0;

const float L1 = 13.2; //cm
const float L2 = 10.5;
const float L12 = L1*L1;
const float L22 = L2*L2;
const float L122 = (L1+L2) * (L1+L2);
const float GEAR_RATIO_1 = 2; // gear1 : gear2
const float GEAR_RATIO_2 = 2;
float x = 0,y = L1+L2;

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
  float thetaP = atan2(y,x);
  Serial.print("h2:" + String(h2) +  + "\tthetaP: " + String(radToDeg(thetaP)) + "\t");

  if((h2 > L122) || isnan(thetaP)){
    Serial.println("ISNAN");
    return;
  }
  arm2Angle = acos((h2 - L12 - L22)/(2*L1*L2));
  arm1Angle = thetaP - asin((L2*sin(arm2Angle))/(sqrt(h2)));
  
  if(arm2Angle < PI/2){
    arm1Angle = PI/2 - arm1Angle;
    arm2Angle = PI/2 - arm2Angle;
  }
  else{
    arm1Angle = -(arm1Angle - PI/2);
    arm2Angle = -(arm2Angle - PI/2);
  }

  // radToDeg
  arm1Angle = radToDeg(arm1Angle);
  arm2Angle = radToDeg(arm2Angle);
  // Set constrain
  arm1Angle = constrain(arm1Angle, -90, 90);
  arm2Angle = constrain(arm2Angle, -170, 170);
  
  Serial.println("x: " + String(x) + "\ty: " + String(y) + "\tAngle1: " + String(arm1Angle) + "\tAngle2: " + String(arm2Angle));
  arm1Angle = arm1Angle * GEAR_RATIO_1;
  arm2Angle = arm2Angle * GEAR_RATIO_2;
  // Wrap around 
//  arm1Angle = wrap_around(arm1Angle);
//  arm2Angle = wrap_around(arm2Angle);
  



  
  
//  endEffectorAngle = 0;
}
