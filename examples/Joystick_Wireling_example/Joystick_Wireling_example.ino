/*
  TinyCircuits Joystick Wireling Example Sketch

  This sketch will print the current direction of
  the joystick to the Serial Monitor.

  Written 15 July 2019
  By Hunter Hykes
  Modified N/A
  By N/A

  https://TinyCircuits.com
*/

#include <Wire.h>
#include "TinyJoystick.h"

#define JS_PORT 0

TinyJoystick joystick = TinyJoystick();

#if defined(ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif

uint8_t reading;

void setup() {
  Wire.begin();
  SerialMonitorInterface.begin(9600);
  
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  
  while(!SerialMonitorInterface);
  
  joystick.begin();
  joystick.init();

  selectPort(JS_PORT);
}

void loop() {
  joystick.getPosition();
  printDir();
  
  delay(5);
}

void selectPort(int port) {
  Wire.beginTransmission(0x70);
  Wire.write(0x04 + port);
  Wire.endTransmission();
}

void printDir() {
  if(joystick.up) {
    SerialMonitorInterface.print("UP");
  }
  if(joystick.down) {
    SerialMonitorInterface.print("DOWN");
  }
  if(joystick.left) {
    SerialMonitorInterface.print("LEFT");
  }
  if(joystick.right) {
    SerialMonitorInterface.print("RIGHT");
  }

  SerialMonitorInterface.println("");
}
