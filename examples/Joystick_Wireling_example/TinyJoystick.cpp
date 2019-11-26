#include "TinyJoystick.h"

#include <inttypes.h>
#include "Arduino.h"
#include <Wire.h>

#if defined(ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif

TinyJoystick::TinyJoystick() {
  // default constructor
}

int TinyJoystick::begin() {
  //Detect address
  I2Caddress = SX1502_I2CADDR;
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
  Wire.beginTransmission(SX1502_I2CADDR);
  Wire.write(regAddr);
  Wire.write(regData);
  Wire.endTransmission();
}

// returns byte stored within specified register
uint8_t TinyJoystick::read(uint8_t regAddr) {
  Wire.beginTransmission(SX1502_I2CADDR);
  Wire.write(regAddr);
  debug = Wire.endTransmission(); // debug set to value returned (error checking)

  // Request one data byte
  Wire.requestFrom(SX1502_I2CADDR, 1);

  SerialMonitorInterface.print("valRead: ");SerialMonitorInterface.print(value);
  
  value = (uint8_t)Wire.read();
}

// initialize SX1502 for use with SH7010
int TinyJoystick::init(void) {
  write(SX1502_REGDIR, 0xFF);           // set I/O to all input
    delay(5);
  write(SX1502_REG_PLD_MODE, 0x00);     // disable PLD input (default)
    delay(5);
  write(SX1502_REG_DATA, 0x00);         // clear contents of register data
    delay(5);
  write(SX1502_REG_PULLUP, 0x9B);       // enable pull-up on IO3, 7, 1, 0, 4 (IO used by Joystick)
    delay(5);
  return debug;
}

// return data from data register
uint8_t TinyJoystick::getRegData(void) {
  value = 0x00;
  value = read(SX1502_REG_DATA);
  return value;
}

// return joystick position
void TinyJoystick::getPosition(void) {
  getRegData();

  SerialMonitorInterface.print("val: ");SerialMonitorInterface.println(value);

  uint8_t dirtyValue = ~value;  // flip bits since active low

  SerialMonitorInterface.print("dirty val: ");SerialMonitorInterface.println(dirtyValue);
  
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

// Reads 8 bits
void TinyJoystick::wireReadRegister(uint8_t reg, uint8_t *value)
{
    Wire.beginTransmission(SX1502_I2CADDR);
    Wire.write(reg);                   
    Wire.endTransmission();
    
    Wire.requestFrom(SX1502_I2CADDR, (uint8_t)1);
    *value = Wire.read();
}




/*
Reads 8 bits of GPIO to determine & then print direction of 
         attached joystick

Added by: Laveréna Wienclaw for TinyCircuits
*/
void TinyJoystick::readJoystick() {
    uint8_t value;
    wireReadRegister(SX1502_REG_DATA, &value);
    
//    SerialMonitorInterface.print("GPIO Read Raw="); // For debugging joystick direction hex code
//    SerialMonitorInterface.println(value,HEX);

    if(value == JOYSTICK_UP || value == JOYSTICK_UP_ALT) {
      up = 1;
//      SerialMonitorInterface.print("JOYSTICK_UP");
    }
    if(value == JOYSTICK_DOWN) {
      down = 1;
//      SerialMonitorInterface.print("JOYSTICK_DOWN");
    }
    if(value == JOYSTICK_LEFT || value == JOYSTICK_LEFT_ALT) {
      left = 1;
//      SerialMonitorInterface.print("JOYSTICK_LEFT");
    }
    if(value == JOYSTICK_RIGHT || value == JOYSTICK_RIGHT_ALT) {
      right = 1;
//      SerialMonitorInterface.print("JOYSTICK_RIGHT");
    }
    if(value == JOYSTICK_NEUTRAL){
      up = 0;
      down = 0;
      left = 0;
      right = 0;
    }
}
