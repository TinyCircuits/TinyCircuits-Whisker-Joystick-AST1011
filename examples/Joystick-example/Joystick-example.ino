/*
  Joystick Example
  Prints to the Serial Monitor the direction the joystick is moved in (Up, down, left, right)
  The "up" direction is the direction closest to the 5-pin connector.

  Written by: Laveréna Wienclaw for TinyCircuits
  Last Updated: March 2020
*/

#include <Wire.h>
#include <Wireling.h>
#include <SX1505.h>             // For interfacing with Joystick and Rotary Switch Wirelings

// Universal TinyCircuits Serial Monitor Config
#if defined (ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif

/* * * * * * * * * * Joystick * * * * * * * * * */
#define JS_PORT 0
TinyJoystick joystick = TinyJoystick(); 

void setup() {
  Wire.begin();
  Wireling.begin();

  /* * * * * * Joystick Init * * * * */
  Wireling.selectPort(JS_PORT); 
  joystick.begin(); 
  
  SerialMonitorInterface.begin(9600);
  delay(500);
}

void loop() {
  joystick.getPosition();
  writeToMonitor();
}

void writeToMonitor() {

  if(joystick.up) {
    SerialMonitorInterface.println("UP (direction facing 5-pin connector)");
  }
  else if(joystick.down) {
    SerialMonitorInterface.println("DOWN");
  }
  else if(joystick.left) {
    SerialMonitorInterface.println("LEFT");
  }
  else if(joystick.right) {
    SerialMonitorInterface.println("RIGHT");
  }
  delay(100);
}
