#include <Arduino.h>
#include <Servo.h>
#define LEFTPIN 8
#define RIGHTPIN 9
#define UPPERTHRESHOLD 120
#define LOWERTHRESHOLD 60

class Drivetrain{
  private:
    Servo servoLeft;
    Servo servoRight;
    int degreesL;
    int degreesR;
    int calculateLeft(int yInputL){
      if(yInputL==255)return 1000;            
      degreesL = map(yInputL, 0,255,180,0);   //maps the joystick position from 0-255 to 180-0 for easier passing into servo angle
      if(degreesL > LOWERTHRESHOLD && degreesL < UPPERTHRESHOLD){     //checking to see if joystick is in the dead zone
        degreesL = 90;                                          //Angle is set to 90 if it is
      }
      return degreesL;
    }
    int calculateRight(int yInputR){        
      if(yInputR==255)return 1000;            
      degreesR = map(yInputR, 0,255,0,180);   //maps the joystick position from 0-255 to 0-180 for easier passing into servo angle
      if(degreesR > LOWERTHRESHOLD && degreesR < UPPERTHRESHOLD){     //checking to see if joystick is in the dead zone
        degreesR = 90;                                          //Angle is set to 90 if it is
      }
      return degreesR;
    }
  public:
    Drivetrain(){};
    void intitialize(){                         //set up the servos
      servoLeft.attach(LEFTPIN);
      servoRight.attach(RIGHTPIN);
      return;
    }
    void forward(int Ljoystick,int Rjoystick){  //move the robot 
      int Lspeed = calculateLeft(Ljoystick);    //getting the angle to write to the left servo
      int Rspeed = calculateRight(Rjoystick);   //getting the angle to write to the right servo
      if(Lspeed!=1000){                         //checks to make sure the original value was not 255
        servoLeft.write(Lspeed);                //write calculated angle to the left servo
      }
      if(Rspeed!=1000){                         //checks to make sure the original value was not 255
        servoRight.write(Rspeed);               //write calculated angle to the left servo
      } 
    }
};
