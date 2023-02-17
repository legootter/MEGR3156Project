/*MEGR 3156 robot code
Group 3
Project uses an Arduino uno as the microcontroller and a ps2 controller.
There are 3 servos and 2 linear actuators powered by a TB6612FNG motor driver
*/

#include <PS2X_lib.h>
#include <Servo.h>
#include "drivetrain.cpp"
#include "gripper.cpp"
#include "crane.cpp"
#define DAT A0              //defining the data pin for the ps2 controller, pin 1
#define CMD A1              //defining the command pin for the ps2 controller, pin 2
#define SEL A2              //defining the attention pin for the ps2 controller, pin 6
#define CLK A3              //defining the clock pin for the ps2 controller, pin 7
int RYPOS=0;                //position (0-255) of the right joystick y axis
int LYPOS=0;                //position (0-255) of the left joystick y axis
bool triggers;              //sets the gripper state identifier
bool HState;                //sets the Horizontal Actuator state identifier
bool VState;                //sets the Vertical Actuator state identifier
PS2X ps2x;
Drivetrain drivetrain;
Gripper gripper;
Crane crane;

void setup() {
  drivetrain.intitialize();               //attach drivetrain servos
  gripper.initialize();                   //attach gripper servo 
  Serial.begin(9600);
  delay(6000);                            //allows controller to successfuly pair
  ps2x.config_gamepad(CLK,CMD,SEL,DAT);   //configures the controller
}

void loop() {
  ps2x.read_gamepad(); //read controller
  if(ps2x.ButtonPressed(PSB_L2)||ps2x.ButtonPressed(PSB_R2)){           //check to see if either the L2 or R2 trigger have been pulled
    if(ps2x.ButtonPressed(PSB_L2))triggers=true;                        //check to see if L2 trigger was pulled
    if(ps2x.ButtonPressed(PSB_R2))triggers=false;                       //check to see if R2 trigger was pulled
    gripper.status(triggers);                                           //Closes/opens the gripper
  }
  if(ps2x.ButtonPressed(PSB_TRIANGLE)||ps2x.ButtonPressed(PSB_CROSS)){  //check to see if either the triangle or cross buttons have been pushed
    if(ps2x.ButtonPressed(PSB_TRIANGLE))VState=true;                    //check to see if Triangle Button was pushed
    if(ps2x.ButtonPressed(PSB_CROSS))VState=false;                      //check to see if Cross Button was pushed
    crane.VMove(VState);                                                //Raise/lower the vertical actuator
  }
  if(ps2x.ButtonPressed(PSB_PAD_UP)||ps2x.ButtonPressed(PSB_PAD_DOWN)){ //check to see if either the D pad up or downbuttons have been pushed
    if(ps2x.ButtonPressed(PSB_PAD_UP))HState=true;                      //check to see if D pad up was pushed
    if(ps2x.ButtonPressed(PSB_PAD_DOWN))HState=false;                   //check to see if D pad down was pushed
    crane.HMove(HState);                                                //Extend/retract the horizontal actuator
  }
  RYPOS=ps2x.Analog(PSS_RY);                                      //get the Right joystick Y axis value
  LYPOS=ps2x.Analog(PSS_LY);                                      //get the Left joystick Y axis value
  drivetrain.forward(LYPOS,RYPOS);                                    //moves servos based on RYPOS and LYPOS
  if(ps2x.ButtonPressed(PSB_SQUARE))crane.stop();
}
