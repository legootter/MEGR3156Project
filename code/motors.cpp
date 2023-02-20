//Team 3
#include <Arduino.h>

class Motors{
  private:
    int PinIn1;
    int PinIn2;
    int PinPWM;
  public:
    Motors(){}
    Motors(int pin1,int pin2, int PWM){                       //motor constructor
      PinIn1=pin1;
      pinMode(PinIn1,OUTPUT);
      PinIn2=pin2;
      pinMode(PinIn2,OUTPUT);
      PinPWM=PWM;
      pinMode(PinPWM,OUTPUT);
    }
    void move(uint8_t PinMode1,uint8_t PinMode2, int PWMS){   //Motor movement option that includes PWM
      digitalWrite(PinIn1,PinMode1);
      digitalWrite(PinIn2,PinMode2);
      analogWrite(PinPWM,PWMS);
    }
    void move(uint8_t PinMode1,uint8_t PinMode2){             //Motor movement option that doesn't includes PWM
      digitalWrite(PinIn1,PinMode1);
      digitalWrite(PinIn2,PinMode2);
    }
};