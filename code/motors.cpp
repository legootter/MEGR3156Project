#include <Arduino.h>

class Motors{
  private:
    int PinIn1;
    int PinIn2;
    int PinPWM;
    int PWMSpeed;
  public:
    Motors(int pin1,int pin2, int PWM){
      PinIn1=pin1;
      pinMode(PinIn1,OUTPUT);
      PinIn2=pin2;
      pinMode(PinIn2,OUTPUT);
      PinPWM=PWM;
      pinMode(PinPWM,OUTPUT);
    }
    void move(uint8_t PinMode1,uint8_t PinMode2, int PWMS){
      digitalWrite(PinIn1,PinMode1);
      digitalWrite(PinIn2,PinMode2);
      analogWrite(PinPWM,PWMS);
    }
    void move(uint8_t PinMode1,uint8_t PinMode2){
      digitalWrite(PinIn1,PinMode1);
      digitalWrite(PinIn2,PinMode2);
    }
};