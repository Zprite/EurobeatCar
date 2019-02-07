#define buttonA_pin 8
#define buttonB_pin 12
#define buttonX_pin 11
#define buttonY_pin 10
#define buttonShoulder_pin 9

#define analogX_pin 6
#define analogY_pin 7
#define stickButton 2

struct controller {
    bool buttonA=0, buttonB=0, buttonX=0, buttonY=0,buttonShoulder=0;
    int stick_xVal;
    int stick_yVal; 
};