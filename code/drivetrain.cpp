#include <Arduino.h>
#include <Servo.h>
#define LEFTPIN 8
#define RIGHTPIN 9


class drivetrain{
    private:
      Servo servoLeft;
      Servo servoRight;
      int upperThreshold = 120;
      int lowerThreshold = 60;
      int degrees;
      int calculateLeft(int yInputL, int xInputL){
        degrees = map(yInputL, 0,255,180,0);
        if(degrees>lowerThreshold&&degrees<upperThreshold){
          degrees = 90;
        }
        return degrees;
      }
      int calculateRight(int yInputR,int xInputR){
        degrees = map(yInputR, 0,255,180,0);
        if(degrees>lowerThreshold&&degrees<upperThreshold){
          degrees = 90;
        }
        return degrees;
      }
    public:
        void intitialize(){
          servoLeft.attach(LEFTPIN);
          servoRight.attach(RIGHTPIN);
          return;
        }
        void foward(int joystick){
          int speed = calculateLeft(joystick,0);
          servoLeft.write(speed);
          servoRight.write(speed);
          Serial.println(speed);
        }
};
