//Team 3
#include "motors.cpp"
#include "Arduino.h"
#define PWMA 3
#define PWMB 5
#define AIN1 2
#define AIN2 4
#define BIN1 6
#define BIN2 7


class Crane{
  private:
    Motors HActuator{AIN1,AIN2,PWMA};       //setting up Horizontal Actuator 
    Motors VActuator{BIN1,BIN2,PWMB};       //setting up Vertical Actuator 
    void HExtend(){                         //Full speed horizontal extend
      HActuator.move(HIGH,LOW,255);
    }
    void HRetract(){                        //Full speed horizontal retract
      HActuator.move(LOW,HIGH,255);
    }
    void HStop(){                           //stops horizontal actuator
      HActuator.move(HIGH,HIGH);
    }
    void VExtend(){                         //Full speed vertical extend
      VActuator.move(HIGH,LOW,255);
    }
    void VRetract(){                        //Full speed vertical retract
      VActuator.move(LOW,HIGH,255);
    }
    void VStop(){                           //stops vertical actuator
      VActuator.move(HIGH, HIGH);
    }
  public:
    Crane(){};
    void VMove(bool state){
      if(state==true) HExtend();  
      else  HRetract();
    }
    void HMove(bool state){
      if(state==true) VExtend();  
      else  VRetract();
    }
    void stop(bool actuator){ 
      if(actuator==true){
        VStop();
      }
      if(actuator==false){
        HStop();
      }
    }
};
