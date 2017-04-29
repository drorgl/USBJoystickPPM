// FrSkyAccessor.h

#ifndef _FRSKYACCESSOR_h
#define _FRSKYACCESSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//#include <SoftwareSerial.h>
//#include "SimpleSoftSerial/sss.h"
#include <FrSky.h>

//SoftwareSerial serial2(7, 8);

class FrSkyAccessor {
private:
	

	FrSky frsky;
public:
	uint8_t link_up;
	uint8_t link_down;
	float a1;
	float a2;
	bool valid_values;
	unsigned long last_update;

	void setup() {
		////serial2.begin(9600);
		//sssBegin(7,8);
		//valid_values = false;
		//link_up = 255;
		//link_down = 255;
	}

	void loop() {
//		//if (serial2.available()) {
//		if (sssAvailable()){
//			//char c = serial2.read();
//			char c = sssRead();
//			if (frsky.update(c)) { // frsky_update() returns 1 if a complete packet was successfully decoded, otherwise 0
//				valid_values = true;
//				link_up = frsky.getLink_up();
//				link_down = frsky.getLink_dn();
//				a1 = frsky.getRX_a1()*0.0517647058824;
//				a2 = frsky.getRX_a2()*0.0129411764706;
//				last_update = millis();
//
//#if 0
//				Serial.print("TX RSSI: ");
//				Serial.println(frsky.getLink_up());
//				Serial.print("Telemetry RSSI: ");
//				Serial.println(frsky.getLink_dn());
//				Serial.print("RX Voltage: ");
//				Serial.println(frsky.getRX_a1()*0.0517647058824); // The internal sensor has a 4:1 divider, so the value is 0-13,2V in 255 steps or 0,052V per step
//				Serial.print("A2 Voltage: ");
//				Serial.println(frsky.getRX_a2()*0.0129411764706); // A2 without divider is 0-3,3V in 255 steps or 0,013V per step
//#endif
//			}
//		}
	}
};

#endif

