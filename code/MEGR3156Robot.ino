/*MEGR 3156 robot code
Group 3: Alex Norris, others..

*/
#include <PS2X_lib.h>   //including the library for connecting to the ps2 controller
#include <Servo.h>      //including the servo library
#include "drivetrain.cpp"   //including the motors class for the robot
#define DAT A0          //defining the data pin for the ps2 controller, pin 1
#define CMD A1          //defining the command pin for the ps2 controller, pin 2
#define SEL A2          //defining the attention pin for the ps2 controller, pin 6
#define CLK A3          //defining the clock pin for the ps2 controller, pin 7
int RYPOS=0;            //position (0-255) of the right joystick y axis
int LYPOS=0;            //position (0-255) of the left joystick y axis
bool triggers;          //
PS2X ps2x;              //creating the ps2 controller object
drivetrain motors;      //creating the motors object

void setup() {
  motors.intitialize(); //attach servos to the pins
  Serial.begin(9600);
  delay(6000);          //allows controller to successfuly pair
  ps2x.config_gamepad(CLK,CMD,SEL,DAT);   //configures the controller
}

void loop() {
  ps2x.read_gamepad(); //read controller
  if(ps2x.ButtonPressed(PSB_L2)||ps2x.ButtonPressed(PSB_R2)){     //check to see if either the L2 or R2 trigger have been pulled
    if(ps2x.ButtonPressed(PSB_L2))triggers=true;                  //check to see if L2 trigger was pulled
    if(ps2x.ButtonPressed(PSB_R2))triggers=false;                 //check to see if R2 trigger was pulled
    motors.gripper(triggers);                                     //Closes/opens the gripper
  }
  RYPOS=ps2x.Analog(PSS_RY);                                      //get the Right joystick Y axis value
  LYPOS=ps2x.Analog(PSS_LY);                                      //get the Left joystick Y axis value
  motors.forward(LYPOS,RYPOS);                                    //moves servos based on RYPOS and LYPOS
}
