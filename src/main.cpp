#include <Arduino.h>
#include "fucntions.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(stickButton,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  struct analogStick anal1;
  anal1 = readAnalogStick(analogX_pin,analogY_pin, stickButton);
  Serial.print("X: ");
  Serial.print(anal1.xVal);
  Serial.print("  |  ");
  Serial.print("Y: ");
  Serial.println(anal1.yVal);
}