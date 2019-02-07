#include <Arduino.h>
#include "global.h"

void readAnalogStick(struct controller* stick , uint8_t xPin, uint8_t yPin, uint8_t stick_button){
    static bool dpiMode = 0;
    int xVal = (analogRead(xPin) * 21 / 1024)-10; //  Read analog resistor value (0-1024), then convert value to fit in a range from -10 to 10.
    int yVal = (analogRead(yPin) * 21 / 1024)-10; // Subtract (maxval/2 -1) to get 0 as deadzone
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
}