#include <Arduino.h>
#include <stdio.h>
#include <SPI.h>
#include <RF24.h>
#include "global.h"
const bool DEBUG = 1;

void setup() {
  Serial.begin(9600);
  // Setup radio
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  // Setup all buttons
  pinMode(stickButton , INPUT_PULLUP); 
  pinMode(buttonA_pin , INPUT_PULLUP);
  pinMode(buttonB_pin , INPUT_PULLUP);
  pinMode(buttonX_pin , INPUT_PULLUP);
  pinMode(buttonY_pin , INPUT_PULLUP);
  pinMode(buttonShoulder_pin , INPUT_PULLUP);
}

void loop() {
  struct controller c1;
  readAnalogStick(&c1, analogX_pin,analogY_pin, stickButton);
  getButtonValues(&c1, buttonA_pin , buttonB_pin , buttonX_pin , buttonY_pin , buttonShoulder_pin);
  if(DEBUG==1)
    serialDebug(&c1);
  char* output= setOutput(&c1);
  sendOutput(output); 
}


void readAnalogStick(struct controller* stick , uint8_t xPin, uint8_t yPin, uint8_t stick_button){
    static bool dpiMode = 0;
    int xVal = (analogRead(xPin) * 19 / 1024)-9; //  Read analog resistor value (0-1024), then convert value to fit in a range from -9 to 9.
    int yVal = (analogRead(yPin) * 19 / 1024)-9; // Subtract (maxval/2 -1) to get 0 as deadzone
    xVal *= -1; // Stick is mounted upside down in our project
    yVal *= -1; 

    bool buttonVal = digitalRead(stick_button);
    if(buttonVal == 0){ // If button has been pressed
      dpiMode = !dpiMode; // Toggle DPI mode
      Serial.println("DPI MODE TOGGLED!");
      delay(200); // Remove double input
    } 
    if(dpiMode == 1){ // Halve sensitivity in DPI mode
      xVal /= 2;
      yVal /= 2;
    }

    stick->stick_xVal=xVal; // Write stick values to struct
    stick->stick_yVal=yVal;
}

void getButtonValues(struct controller* buttonSet, uint8_t buttonA , uint8_t buttonB, uint8_t buttonX, uint8_t buttonY, uint8_t buttonShoulder){
  buttonSet->buttonA=digitalRead(buttonA);
  buttonSet->buttonB=digitalRead(buttonB);
  buttonSet->buttonX=digitalRead(buttonX);
  buttonSet->buttonY=digitalRead(buttonY);
  buttonSet->buttonShoulder=digitalRead(buttonShoulder);
}

void serialDebug(struct controller* c1){
  Serial.print("X: ");
  Serial.print(c1->stick_xVal);
  Serial.print("  |  ");
  Serial.print("Y: ");
  Serial.println(c1->stick_yVal);
  Serial.print("A BUTTON: ");
  Serial.println(c1->buttonA);
  Serial.print("B BUTTON: ");
  Serial.println(c1->buttonB);
  Serial.print("X BUTTON: ");
  Serial.println(c1->buttonX);
  Serial.print("Y BUTTON: ");
  Serial.println(c1->buttonY);
  Serial.print("SHOULDER BUTTON: ");
  Serial.println(c1->buttonShoulder);
  delay(1000);
  //TENIS
}

char* setOutput (struct controller* c1){
  char output [32];
  // STRUCTURE OF OUTPUT ARRAY : 
  //  [ x-axis  y-axis , A , B , X , Y , SHOULDER]
  output[0] = c1->stick_yVal;
  output[1] = c1->stick_xVal;
  output[2] = c1->buttonA;
  output[3] = c1->buttonB;
  output[4] = c1->buttonX;
  output[5] = c1->buttonY;
  output[6] = c1->buttonShoulder;
  
  return output;
}

int sendOutput (char* output) {
  radio.write(&output, sizeof(output));
  delay(1000); 
}  