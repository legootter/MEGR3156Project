//Team 3
#include "Arduino.h"
#include <Servo.h>
#define HActPin 9
#define VActPin 10

class Crane{
  private:
    Servo HActuator;
    Servo VActuator;
    int HFULL=1400;//Horizontal only gets extended 40%
    int VFULL=2000;//Vertical gets fully extended
    int FULLRETRACT=1000;
  public:
    Crane(){}
    void extend(bool actuator){//true=Horizontal false=Vertical
      if(actuator==true){
        HActuator.writeMicroseconds(HFULL);
      }
      else VActuator.writeMicroseconds(VFULL);
    }
    void retract(bool actuator){
      if(actuator==true){
        HActuator.writeMicroseconds(FULLRETRACT);
      }
      else VActuator.writeMicroseconds(FULLRETRACT);
    }
    void move(int ms,bool actuator){
      if(ms<0||ms>2000)return;
      if(actuator==true){
        HActuator.writeMicroseconds(ms);
      }
      else VActuator.writeMicroseconds(ms);
    }
    void intitialize(){                         //set up the servos
      HActuator.attach(HActPin);
      VActuator.attach(VActPin);
      return;
    }
};
