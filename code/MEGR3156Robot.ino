/*MEGR 3156 robot code
Team 3
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
  ps2x.read_gamepad();                                                  //read controller
  if(ps2x.ButtonPressed(PSB_L2))gripper.status(true);                   //Releases gripper if L2 is pulled
  if(ps2x.ButtonPressed(PSB_R2))gripper.status(false);                  //Engages gripper if R2 is pulled

  if(ps2x.Button(PSB_TRIANGLE)||ps2x.Button(PSB_CROSS)){                //Checks to see if Triangle or Cross is being held
    if(ps2x.Button(PSB_TRIANGLE))crane.VMove(true);                     //If triangle is being pushed, raise Vertical Actuator
    if(ps2x.Button(PSB_CROSS))crane.VMove(false);                       //If X is being pushed, lower Vertical Actuator
  }
  else crane.stop(true);                                                //Stops Actuator when button is not being pressed
  
  if(ps2x.Button(PSB_PAD_UP)||ps2x.Button(PSB_PAD_DOWN)){               //check to see if either the D pad up or downbuttons have been pushed
    if(ps2x.Button(PSB_PAD_UP))crane.HMove(true);                       //check to see if D pad up was pushed
    if(ps2x.Button(PSB_PAD_DOWN))crane.HMove(false);                    //check to see if D pad down was pushed                                               //Extend/retract the horizontal actuator
  }
  else crane.stop(false);

  RYPOS=ps2x.Analog(PSS_RY);                                            //get the Right joystick Y axis value
  LYPOS=ps2x.Analog(PSS_LY);                                            //get the Left joystick Y axis value
  drivetrain.forward(LYPOS,RYPOS);                                      //moves servos based on RYPOS and LYPOS
}
