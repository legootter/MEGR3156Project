#include <PS2X_lib.h>
#include <Servo.h>
#include "drivetrain.cpp"
#define DAT A0
#define CMD A1
#define SEL A2
#define CLK A3
int LYPOS=0;
PS2X ps2x;
drivetrain motors;

void setup() {
  motors.intitialize();
  Serial.begin(9600);
  delay(6000);
  ps2x.config_gamepad(CLK,CMD,SEL,DAT);
}

void loop() {
  ps2x.read_gamepad(); //read controller and set large motor to spin at 'vibrate' speed   
  LYPOS=ps2x.Analog(PSS_LY);
  if(LYPOS==255)return;
  motors.foward(LYPOS);
}
