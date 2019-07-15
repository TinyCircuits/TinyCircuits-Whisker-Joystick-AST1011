/*
  TinyCircuits Joystick Whisker Example Sketch

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

#define JS_PORT 2

TinyJoystick js = TinyJoystick();

uint8_t reading;

void setup() {
  Wire.begin();
  SerialUSB.begin(9600);
  
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  
  while(!SerialUSB);
  
  js.begin();
  js.init();

  selectPort(JS_PORT);
}

void loop() {
  js.getPosition();
  printDir();
  
  delay(5);
}

void selectPort(int port) {
  Wire.beginTransmission(0x70);
  Wire.write(0x04 + port);
  Wire.endTransmission();
}

void printDir() {
  if(js.up) {
    SerialUSB.print("UP");
  }
  if(js.down) {
    SerialUSB.print("DOWN");
  }
  if(js.left) {
    SerialUSB.print("LEFT");
  }
  if(js.right) {
    SerialUSB.print("RIGHT");
  }

  SerialUSB.println("");
}
