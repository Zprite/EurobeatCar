#include <Arduino.h>
#include "fucntions.h"

const bool DEBUG = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(stickButton , INPUT_PULLUP); // Setup all buttons
  pinMode(buttonA_pin , INPUT_PULLUP);
  pinMode(buttonB_pin , INPUT_PULLUP);
  pinMode(buttonX_pin , INPUT_PULLUP);
  pinMode(buttonY_pin , INPUT_PULLUP);
  pinMode(buttonShoulder_pin , INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  struct controller c1;
  readAnalogStick(&c1, analogX_pin,analogY_pin, stickButton);
  getButtonValues(&c1, buttonA_pin , buttonB_pin , buttonX_pin , buttonY_pin , buttonShoulder_pin);
  if(DEBUG==1)
    serialDebug(&c1);
}