/*
  TinyCircuits Joystick Wireling Example Sketch

  This sketch will print the current direction of
  the joystick to the Serial Monitor.

  Written 15 July 2019
  By Hunter Hykes
  Modified 4 November 2019
  By Laveréna Wienclaw

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

  selectPort(JS_PORT);
  
  joystick.begin();
  joystick.init();
}

void loop() {
  setup();
  joystick.readJoystick();
  printDir();
  delay(5);
}

void printDir() {
  if(joystick.up) {
    SerialMonitorInterface.print("UP");
    SerialMonitorInterface.println();
  }
  if(joystick.down) {
    SerialMonitorInterface.print("DOWN");
    SerialMonitorInterface.println();
  }
  if(joystick.left) {
    SerialMonitorInterface.print("LEFT");
    SerialMonitorInterface.println();
  }
  if(joystick.right) {
    SerialMonitorInterface.print("RIGHT");
    SerialMonitorInterface.println();
  }  
}

void selectPort(int port) {
  Wire.beginTransmission(0x70);
  Wire.write(0x04 + port);
  Wire.endTransmission();
}
