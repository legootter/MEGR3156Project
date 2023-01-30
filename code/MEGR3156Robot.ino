#include <PS2X_lib.h>
#include <Servo.h>
#include "drivetrain.cpp"
#define DAT A0
#define CMD A1
#define SEL A2
#define CLK A3
int RYPOS=0;
int LYPOS=0;
bool triggers;
PS2X ps2x;
drivetrain motors;

void setup() {
  motors.intitialize();
  Serial.begin(9600);
  delay(6000);
  ps2x.config_gamepad(CLK,CMD,SEL,DAT);
}

void loop() {
  ps2x.read_gamepad(); //read controller
  if(ps2x.ButtonPressed(PSB_L2)||ps2x.ButtonPressed(PSB_R2)){
    if(ps2x.ButtonPressed(PSB_L2))triggers=true;
    if(ps2x.ButtonPressed(PSB_R2))triggers=false;
    motors.gripper(triggers);
  }
  RYPOS=ps2x.Analog(PSS_RY);
  LYPOS=ps2x.Analog(PSS_LY);
  motors.forward(LYPOS,RYPOS);
}
