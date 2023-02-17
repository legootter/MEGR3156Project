#include <Arduino.h>
#include <Servo.h>
#define OPEN 180
#define CLOSED 0
#define GRIPPERPIN 10

class Gripper{
  private:
    Servo gripper;
    bool state;                                     //open=true closed=false
  public:
    Gripper(){};
    void initialize(){
      gripper.attach(GRIPPERPIN);
    }
    void status(bool mode){                     //Close/Open the gripper
      if(state==mode)return;                    //checks to see if the current state of the gripper is what what inputted
      if(mode==true){                           //L2 has been pressed
        gripper.write(OPEN);                    //open the gripper
        state=mode;                              //sets the boolean check to open
      }
      if(mode==false){                          //R2 has been pressed
        gripper.write(CLOSED);                  //close the gripper
        state=mode;                             //sets the boolean check to closed
      } 
    }
};
