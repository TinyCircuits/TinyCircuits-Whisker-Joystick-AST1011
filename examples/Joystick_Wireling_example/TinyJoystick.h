/*
SH7010 Arduino Library
Written 07/10/2019
By Hunter Hykes for TinyCircuits

Written for use with the Joystick Wireling featuring the
SX1502 I2C I/O Expander and the SKRHABE010 Digital Joystick

Modified 11/04/2019 By Laveréna Wienclaw for TinyCircuits
 - Fixed compatibility for ATmega328P and SAMD21 platforms
*/

#ifndef TINYJOYSTICK_h
#define TINYJOYSTICK_h

// Definitions for SX1502 I2C I/O Expander
#define SX1502_I2CADDR			  0x20

#define SX1502_REG_DATA			  0x00
#define SX1502_REGDIR			    0x01	// 0 -> output, 1 -> input
#define SX1502_REG_PULLUP		  0x02 	// 0 -> pull-up disabled, 1 -> pull-up enabled
#define SX1502_REG_PULLDOWN   0x03

#define SX1502_REG_INT_MASK		0x05
#define SX1502_REG_SENSE_HI		0x06
#define SX1502_REG_SENSE_LO		0x07
#define SX1502_REG_INT_SRC		0x08
#define SX1502_REG_EVENT_STAT	0x09
#define SX1502_REG_PLD_MODE		0x10
#define SX1502_REG_PLD_T0		  0x11
#define SX1502_REG_PLD_T1		  0x12
#define SX1502_REG_PLD_T2		  0x13
#define SX1502_REG_PLD_T3		  0x14
#define SX1502_REG_PLD_T4		  0x15
#define SX1502_REG_ADVANCED   0xAB

// NOTE: UP is the direction if pushing the
// joystick towards the whisker connector.
// Joystick definitions
#define JOYSTICK_UP        0xB9
#define JOYSTICK_UP_ALT    0xF9  
#define JOYSTICK_DOWN      0x3B  
#define JOYSTICK_LEFT      0xBA 
#define JOYSTICK_LEFT_ALT  0xFA  
#define JOYSTICK_RIGHT     0xB3  
#define JOYSTICK_RIGHT_ALT 0xF3  
#define JOYSTICK_PRESS     0xAB  
#define JOYSTICK_NEUTRAL   0xBB  

#include <inttypes.h>

class TinyJoystick {
public:
	TinyJoystick(void);
	int begin(void);
	void write(uint8_t, uint8_t);
	uint8_t read(uint8_t);
	int init(void);
	uint8_t getRegData(void);
	void getPosition(void);
  void readJoystick(void);
  void wireReadRegister(uint8_t reg, uint8_t *value);

	uint8_t value;
	uint8_t debug;
	uint8_t I2Caddress = 0;

	uint8_t up = 0;
	uint8_t down = 0;
	uint8_t left = 0;
	uint8_t right = 0;
};

#endif
