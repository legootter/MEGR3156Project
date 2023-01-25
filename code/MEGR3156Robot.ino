#include <PS2X_lib.h>
#include <Servo.h>
#define DAT A0
#define CMD A1
#define SEL A2
#define CLK A3

PS2X ps2x;

void setup() {
  Serial.begin(9600);
  delay(6000);
  ps2x.config_gamepad(CLK,CMD,SEL,DAT);
}

void loop() {
    ps2x.read_gamepad(); //read controller and set large motor to spin at 'vibrate' speed   
    Serial.println(ps2x.Analog(PSS_LY));
    delay(100);
}
