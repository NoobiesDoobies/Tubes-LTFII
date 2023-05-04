#include <Servo.h>

const int SERVO1_PIN = 14; // pin for servo motor
const int SERVO2_PIN = 13;

const int delay_servo = 500;


Servo servo1;
Servo servo2;

enum{DOWN, MIDDLE, UP}; 
int endEffectorState = UP;
int z = 2;

int initialAngle1 = 0;
int initialAngle2 = 0;

void initServo(){
    // set servo pin as output
  pinMode(SERVO1_PIN, OUTPUT);
  pinMode(SERVO2_PIN, OUTPUT); 
  // attach servo to pin
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);

  servo1.write(initialAngle1);
  servo2.write(initialAngle2);

  Serial.println("Servo is Ready");
}

void moveServo(){
//  Serial.println("Moving servo to");
  
  switch(endEffectorState){
      case DOWN:
      {
        if(z == 1){
          endEffectorState = MIDDLE;
          servo1.write(150);
          servo2.write(180);
          Serial.println("150 180");
          delay(delay_servo);
          servo1.write(150);
          servo2.write(150);
          Serial.println("150 150");
          
          
          delay(delay_servo);
          Serial.println("DOWN TO MID");
        }
        break;
      }

      case UP:
        {
          if(z == 1){
            endEffectorState = MIDDLE;
            servo1.write(180);
            servo2.write(150);
//            Serial.println("180 150");
//            Serial.println("150 150");
            
            delay(delay_servo);
            Serial.println("UP TO MID");
          }
          break;
        }
      case MIDDLE:
      {
        if(z == 0){
          endEffectorState = DOWN;
          servo1.write(150);
          servo2.write(180);
//          Serial.println("150 180");
          delay(delay_servo);
          servo1.write(20);
          servo2.write(180);
//          Serial.println("20 180");
          delay(delay_servo);
          Serial.println("MID TO DOWN");
        }
        if(z == 2){
          endEffectorState = UP;
          servo1.write(150);
          servo2.write(150);
//          Serial.println("180 150");
          delay(delay_servo);
          servo2.write(20);
          servo1.write(150);
          delay(delay_servo);
          Serial.println("MID TO UP");
        }
        break;
      }
        
    }
    


}
