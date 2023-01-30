#include <Arduino.h>
#include <Servo.h>
#define LEFTPIN 8
#define RIGHTPIN 9
#define upperThreshold 120
#define lowerThreshold 60


class drivetrain{
    private:
      Servo servoLeft;
      Servo servoRight;
      int degreesL;
      int degreesR;
      bool closed;
      int calculateLeft(int yInputL){
        if(yInputL==255)return 1000;
        degreesL = map(yInputL, 0,255,180,0);
        if(degreesL>lowerThreshold&&degreesL<upperThreshold){
          degreesL = 90;
        }
        return degreesL;
      }
      int calculateRight(int yInputR){        
        if(yInputR==255)return 1000;
        degreesR = map(yInputR, 0,255,0,180);
        if(degreesR>lowerThreshold&&degreesR<upperThreshold){
          degreesR = 90;
        }
        return degreesR;
      }
    public:
        void intitialize(){
          servoLeft.attach(LEFTPIN);
          servoRight.attach(RIGHTPIN);
          return;
        }
        void forward(int Ljoystick,int Rjoystick){
          int Lspeed = calculateLeft(Ljoystick);
          int Rspeed = calculateRight(Rjoystick);
          if(Lspeed!=1000){
            servoLeft.write(Lspeed);
          }
          if(Rspeed!=1000){
            servoRight.write(Rspeed);
          } 
        }
        void gripper(bool mode){
          if(mode==closed)return;
          if(mode==true){
            Serial.println("Gripper opened");
            closed=mode;
            //Open the servo here
          }
          if(mode==false){
            //Close the servo here
            Serial.println("Gripper closed");
            closed=mode;
          }
          
        }
};
