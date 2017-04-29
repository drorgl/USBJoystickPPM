//Originally written by Dennis Frie 2012
//Modified by Dror Gluska 2017

#ifndef _PPMGENERATOR_h
#define _PPMGENERATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
//
//// Dead-time between each channel in the PPM-stream. 
//#define DEAD_TIME 800
//
//// Number of PPM channels out. 1 - 12 channels supported (both incl). 
//#define NUMBER_OF_CHANNELS 8
//
//// Set frame-length depending on channels
//#define FRAME_LENGTH 5003+NUMBER_OF_CHANNELS*5000

class PPMGenerator
{
 protected:
	 byte _pin;

	 
 public:
	void init(byte pin);

	void set_value(byte channel, int value);

	void pause();

	void resume();
};


#endif

