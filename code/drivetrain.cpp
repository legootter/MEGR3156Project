#include <Arduino.h>          //included the main arduino library
#include <Servo.h>            //includes the servo library
#define LEFTPIN 8             //sets the left servvo data pin
#define RIGHTPIN 9            //sets the right servo data pin
#define upperThreshold 120    //sets the upper deadzone limit for the joystick
#define lowerThreshold 60     //set the lower deadzone limit for the joystick


class drivetrain{
    private:
      Servo servoLeft;        //create a servo object for the left wheel
      Servo servoRight;       //create a servo object for the right wheel
      int degreesL;           //initialize the left joystick position variable
      int degreesR;           //initialize the right joystick position variable
      bool closed;            //initialize the check to see if the gripper is closed
      int calculateLeft(int yInputL){
        if(yInputL==255)return 1000;            //bandaid fix for Logitech controller potentiometers going bad
        degreesL = map(yInputL, 0,255,180,0);   //maps the joystick position from 0-255 to 180-0 for easier passing into servo angle
        if(degreesL>lowerThreshold&&degreesL<upperThreshold){     //checking to see if joystick is in the dead zone
          degreesL = 90;                                          //if it is then set the angle to 90 (no motion for continuous servo)
        }
        return degreesL;                                          //returns the angle as an integer
      }
      int calculateRight(int yInputR){        
        if(yInputR==255)return 1000;            //bandaid fix for Logitech controller potentiometers going bad
        degreesR = map(yInputR, 0,255,0,180);   //maps the joystick position from 0-255 to 0-180 for easier passing into servo angle
        if(degreesR>lowerThreshold&&degreesR<upperThreshold){     //checking to see if joystick is in the dead zone
          degreesR = 90;                                          //if it is then set the angle to 90 (no motion for continuous servo)
        }
        return degreesR;                                          //returns the angle as an integer
      }
    public:
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
        void gripper(bool mode){                    //Close/Open the gripper
          if(mode==closed)return;                   //checks to see if the current state of the gripper is what what inputted
          if(mode==true){                           //L2 has been pressed
            Serial.println("Gripper opened");
            closed=mode;                            //sets the boolean check to open
            //Open the servo here
          }
          if(mode==false){                          //checks to see if the current state of the gripper is what what inputted
            //Close the servo here
            Serial.println("Gripper closed");
            closed=mode;                            //sets the boolean check to closed
          }
          
        }
};
