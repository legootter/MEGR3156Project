#include <Arduino.h>
#include <Servo.h>
#define LEFTPIN 8                   //sets the left servvo data pin
#define RIGHTPIN 9                  //sets the right servo data pin
#define UPPERTHRESHOLD 120          //sets the upper deadzone limit for the joystick
#define LOWERTHRESHOLD 60           //set the lower deadzone limit for the joystick

class Drivetrain{
  private:
    Servo servoLeft;        //create a servo object for the left wheel
    Servo servoRight;       //create a servo object for the right wheel
    int degreesL;           //initialize the left joystick position variable
    int degreesR;           //initialize the right joystick position variable
    int calculateLeft(int yInputL){
      if(yInputL==255)return 1000;            
      degreesL = map(yInputL, 0,255,180,0);   //maps the joystick position from 0-255 to 180-0 for easier passing into servo angle
      if(degreesL > LOWERTHRESHOLD && degreesL < UPPERTHRESHOLD){     //checking to see if joystick is in the dead zone
        degreesL = 90;                                          //if it is then set the angle to 90 (no motion for continuous servo)
      }
      return degreesL;                                          //returns the angle as an integer
    }
    int calculateRight(int yInputR){        
      if(yInputR==255)return 1000;            
      degreesR = map(yInputR, 0,255,0,180);   //maps the joystick position from 0-255 to 0-180 for easier passing into servo angle
      if(degreesR > LOWERTHRESHOLD && degreesR < UPPERTHRESHOLD){     //checking to see if joystick is in the dead zone
        degreesR = 90;                                          //if it is then set the angle to 90 (no motion for continuous servo)
      }
      return degreesR;                                          //returns the angle as an integer
    }
  public:
    Drivetrain(){};
    void intitialize(){                         //set up the servos
      servoLeft.attach(LEFTPIN);                //attaching the left servo
      servoRight.attach(RIGHTPIN);              //attaching the right servo
      return;
    }
    void forward(int Ljoystick,int Rjoystick){  //move the robot 
      int Lspeed = calculateLeft(Ljoystick);    //getting the angle to write to the left servo
      int Rspeed = calculateRight(Rjoystick);   //getting the angle to write to the right servo
      if(Lspeed!=1000){                         //checks to make sure the original value was not 255
        servoLeft.write(Lspeed);                //if it wasn't, then write calculated angle to the left servo
      }
      if(Rspeed!=1000){                         //checks to make sure the original value was not 255
        servoRight.write(Rspeed);               //if it wasn't, then write calculated angle to the left servo
      } 
    }
};
