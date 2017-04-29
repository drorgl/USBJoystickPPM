// LCDDisplay.h

#ifndef _LEDDISPLAY_h
#define _LEDDISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <TM1637Display.h>

TM1637Display lcd(4, 3);
uint8_t lcddisplay[4];




class LEDDisplay {
private:
	

	

	void display_rc(byte flight_mode, bool channel5, byte camera_mode, bool camera_auto_center) {
		lcddisplay[0] = lcd.encodeDigit(flight_mode);
		lcddisplay[1] = (channel5) ? SEG_A | SEG_G | SEG_D : 0;
		lcddisplay[2] = lcd.encodeDigit(camera_mode);
		lcddisplay[3] = (camera_auto_center) ? SEG_F | SEG_B | SEG_E | SEG_C : SEG_G;
		lcd.setSegments(lcddisplay, 4, 0);
	}
public:
	void setup() {
		lcd.setBrightness(0x0a);
		display_clear();
		lcd.showNumberDec(8888);
	}

	void display(byte flight_mode, bool channel5, byte camera_mode, bool camera_auto_center) {
		display_rc(flight_mode, channel5, camera_mode, camera_auto_center);
	}

	void loop() {

	}

	void display_oerr() {
		lcddisplay[0] = SEG_G | SEG_E | SEG_C | SEG_D;
		lcddisplay[1] = SEG_A | SEG_G | SEG_F | SEG_E | SEG_D;
		lcddisplay[2] = SEG_G | SEG_E;
		lcddisplay[3] = SEG_G | SEG_E;
		lcd.setSegments(lcddisplay, 4, 0);
	}

	void display_herr() {
		lcddisplay[0] = SEG_F | SEG_B | SEG_G | SEG_E | SEG_C;
		lcddisplay[1] = SEG_A | SEG_G | SEG_F | SEG_E | SEG_D;
		lcddisplay[2] = SEG_G | SEG_E;
		lcddisplay[3] = SEG_G | SEG_E;
		lcd.setSegments(lcddisplay, 4, 0);
	}

	void display_clear() {
		lcddisplay[0] = SEG_G;
		lcddisplay[1] = SEG_G;
		lcddisplay[2] = SEG_G;
		lcddisplay[3] = SEG_G;
		lcd.setSegments(lcddisplay, 4, 0);
	}
};

#endif

