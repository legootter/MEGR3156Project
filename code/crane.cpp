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
    Motors HActuator{AIN1,AIN2,PWMA};
    Motors VActuator{BIN1,BIN2,PWMB};
  public:
    Crane(){};
    void HExtend(){
      HActuator.move(HIGH,LOW,255);
    }
    void HRetract(){
      HActuator.move(LOW,HIGH,255);
    }
    void HStop(){
      HActuator.move(HIGH,HIGH);
    }
    void VExtend(){
      VActuator.move(HIGH,LOW,255);
    }
    void VRetract(){
      VActuator.move(LOW,HIGH,255);
    }
    void VStop(){
      VActuator.move(HIGH, HIGH);
    }
};