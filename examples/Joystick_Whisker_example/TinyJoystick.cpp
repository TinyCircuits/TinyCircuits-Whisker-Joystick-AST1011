#include "TinyJoystick.h"

#include <inttypes.h>
#include "Arduino.h"
#include <Wire.h>

TinyJoystick::TinyJoystick() {
  // default constructor
}

int TinyJoystick::begin() {
  //Detect address
  I2Caddress = SX1505_I2CADDR;
  Wire.beginTransmission(I2Caddress);
  if (Wire.endTransmission()) {         // if data is too long or ERROR
    I2Caddress++;                       // increment address
    Wire.beginTransmission(I2Caddress); // write to new address (the next address)
    if (Wire.endTransmission()) {       // if data is too long or ERROR
      I2Caddress = 0;                   // set address to 0
      return -1;                        // return -1 to indicate an error
    }             // better to return value given by Wire.endTransmission?
  }
  return 0;       // return 0 to indicate that the first transmission succeeded
}

// writes byte "regData" to register "regAddr"
void TinyJoystick::write(uint8_t regAddr, uint8_t regData) {
  Wire.beginTransmission(SX1505_I2CADDR);
  Wire.write(regAddr);
  Wire.write(regData);
  Wire.endTransmission();
}

// returns byte stored within specified register
uint8_t TinyJoystick::read(uint8_t regAddr) {
  Wire.beginTransmission(SX1505_I2CADDR);
  Wire.write(regAddr);
  debug = Wire.endTransmission(); // debug set to value returned (error checking)

  // Request one data byte
  Wire.requestFrom(SX1505_I2CADDR, 1);
  
  value = (uint8_t)Wire.read();
}

// initialize SX1505 for use with SH7010
int TinyJoystick::init(void) {
  write(SX1505_REGDIR, 0xFF);           // set I/O to all input
    delay(5);
  write(SX1505_REG_PLD_MODE, 0x00);     // disable PLD input (default)
    delay(5);
  write(SX1505_REG_DATA, 0x00);         // clear contents of register data
    delay(5);
  write(SX1505_REG_PULLUP, 0x9B);       // enable pull-up on IO3, 7, 1, 0, 4 (IO used by Joystick)
    delay(5);
  return debug;
}

// return data from data register
uint8_t TinyJoystick::getRegData(void) {
  value = 0x00;
  value = read(SX1505_REG_DATA);
  return value;
}

// return joystick position
void TinyJoystick::getPosition(void) {
  getRegData();

  uint8_t dirtyValue = ~value;  // flip bits since active low
  
  if(dirtyValue & JOYSTICK_UP) {
    up = 1;
  }
  if(dirtyValue & JOYSTICK_DOWN) {
    down = 1;
  }
  if(dirtyValue & JOYSTICK_LEFT) {
    left = 1;
  }
  if(dirtyValue & JOYSTICK_RIGHT) {
    right = 1;
  }
  if (dirtyValue == JOYSTICK_NEUTRAL){
    up = 0;
    down = 0;
    left = 0;
    right = 0;
  }
}
