//// 
//// 
//// 
//
#include "PPMGenerator.h"
//
//byte channel_number = 1;
//int channel_value[13];
//
//void PPMGenerator::init(byte pin)
//{
//	_pin = pin;
//
//
//	pinMode(_pin, OUTPUT);
//
//	TCCR1A =
//		(0 << WGM10) |
//		(0 << WGM11) |
//		(0 << COM1A1) |
//		(1 << COM1A0) | // Toggle pin om compare-match
//		(0 << COM1B1) |
//		(0 << COM1B0);
//
//	TCCR1B =
//		(0 << ICNC1) | // 
//		(0 << ICES1) | //     
//		(0 << CS10) | //Prescale 8  
//		(1 << CS11) | //Prescale 8  
//		(0 << CS12) | //Prescale 8
//		(1 << WGM13) |
//		(1 << WGM12); // CTC mode (Clear timer on compare match) with ICR1 as top.       
//
//	TIMSK1 =
//		(1 << OCIE1A) | // Interrupt on compare A
//		(0 << OCIE1B) | // Disable interrupt on compare B    
//		(0 << TOIE1);
//
//	OCR1A = DEAD_TIME;
//
//	// Frame length set by counter TOP, we use ICR1 as TOP. 
//	ICR1 = FRAME_LENGTH;
//}
//
//void PPMGenerator::set_value(byte channel, int value) {
//	channel_value[channel] = value;
//}
//
//// ===========================
//// Timer 1 compare A vector
//// ===========================
//
//ISR(TIMER1_COMPA_vect) {
//
//
//	if (OCR1A == 0) {
//		TCCR1A =
//			(0 << WGM10) |
//			(0 << WGM11) |
//			(1 << COM1A1) |
//			(1 << COM1A0) |
//			(0 << COM1B1) |
//			(0 << COM1B0);
//
//		channel_number = 1;
//		OCR1A = DEAD_TIME;
//	}
//
//
//	else {
//		if (channel_number == 1) {
//
//			// After first time, when pin have been set hgih, we toggle the pin at each interrupt
//			TCCR1A =
//				(0 << WGM10) |
//				(0 << WGM11) |
//				(0 << COM1A1) |
//				(1 << COM1A0) |
//				(0 << COM1B1) |
//				(0 << COM1B0);
//
//		}
//
//
//		if ((channel_number - 1) < NUMBER_OF_CHANNELS * 2) {
//
//			if ((channel_number - 1) % 2 == 1) {
//				OCR1A += DEAD_TIME;
//			}
//
//			else {
//				OCR1A += channel_value[(channel_number + 1) / 2];
//			}
//
//			channel_number++;
//		}
//
//		// Used to set the pulse low just before the new frame.
//
//
//
//		else {
//			OCR1A = 0; //FRAME_LENGTH-5;
//
//		}
//
//	}
//
//
//}
//
//
//// ===========================
//// Timer 1 compare B vector
//// ===========================
//ISR(TIMER1_COMPB_vect) {
//
//	/*
//	// Pin should be set high first time:
//	TCCR1A =
//	(0<<WGM10) |
//	(0<<WGM11) |
//	(1<<COM1A1) |
//	(1<<COM1A0) |
//	(0<<COM1B1) |
//	(0<<COM1B0);
//
//	channel_number =1;
//	OCR1A = DEAD_TIME;
//	*/
//}


//#include "PPM_Encoder.h"

//#include <outputchannel.h>
//#include <PPMOut.h>
//#include <Timer1.h>

#include "PPM/outputchannel.h"
#include "PPM/PPMOut.h"
#include "PPM/Timer1.h"


#define CHANNELS 8

rc::PPMOut g_PPMOut(CHANNELS);

void PPMGenerator::init(byte pin) {
	//ppm_encoder_init(pin);
	//setup_ppm(pin);

	// Initialize timer1, this is required for all features that use Timer1
	// (PPMIn/PPMOut/ServoIn/ServoOut)
	rc::Timer1::init();

	for (uint8_t i = 0; i < CHANNELS; ++i)
	{

		// fill input buffer, convert raw values to microseconds
		// we'll need to cast our iterator to an OutputChannel, but ugly but safe
		rc::setOutputChannel(static_cast<rc::OutputChannel>(i),1500);
	}

	rc::setOutputChannel(static_cast<rc::OutputChannel>(3), 700);

	// initialize PPMOut with some settings
	g_PPMOut.setPulseLength(448);   // pulse length in microseconds
	g_PPMOut.setPauseLength(10448); // length of pause after last channel in microseconds
									// note: this is also called the end of frame, or start of frame, and is usually around 10ms

									// start PPMOut, use pin 9 (pins 9 and 10 are preferred)
	g_PPMOut.start(pin);
}

void PPMGenerator::set_value(byte channel, int value) {
	//ppm_write_channel(channel, value);
	//ppm[channel] = value;
	rc::setOutputChannel(static_cast<rc::OutputChannel>(channel), value);
	g_PPMOut.update();
}

void PPMGenerator::pause() {
	//pause_ppm = true;
	//while (!ppm_paused) {
	//	delay(1);
	//}
}

void PPMGenerator::resume() {
	//pause_ppm = false;
}