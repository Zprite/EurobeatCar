#include <Arduino.h>
#include "global.h"

struct analogStick readAnalogStick(uint8_t xPin, uint8_t yPin, uint8_t stick_button){
    struct analogStick s1;
    static bool dpiMode = 0;
    int xVal = (analogRead(xPin) * 21 / 1024)-10; //  Read analog resistor value (0-1024), then convert value to fit in a range from -10 to 10.
    int yVal = (analogRead(yPin) * 21 / 1024)-10; // Subtract (maxval/2 -1) to get 0 as deadzone
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

    s1.xVal=xVal;
    s1.yVal=yVal;
    return s1;
}