/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Timer1.cpp
** Timer1 functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include "rc_debug_lib.h"
#include "Timer1.h"


// Static variables
static rc::Timer1::Callback s_TOIE1Callback = 0;
static rc::Timer1::Callback s_OCI1ACallback = 0;
static rc::Timer1::Callback s_OCI1BCallback = 0;
bool s_debug = false;

namespace rc
{

// Public functions

void Timer1::init(bool p_debug)
{
	RC_TRACE("init debug: %d", p_debug);
	s_debug = p_debug;
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1C = 0;
	TIMSK1 = 0;
	OCR1A = 0;
	OCR1B = 0;
	TCNT1 = 0;
}


void Timer1::start()
{
	RC_TRACE("start");
	TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11) | _BV(CS10))) |
	         s_debug ? (_BV(CS12) | _BV(CS10)) :  _BV(CS11);
}


bool Timer1::isRunning()
{
	return (TCCR1B & (_BV(CS12) | _BV(CS11) | _BV(CS10))) != 0;
}


void Timer1::stop()
{
	RC_TRACE("stop");
	TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));
}


void Timer1::setCompareMatch(bool p_enable, bool p_OCIE1A, Callback p_callback)
{
	RC_TRACE("set compare match enable: %d OCIE1A: %d Callback: %p", p_enable, p_OCIE1A, p_callback);
	if (p_enable)
	{
		if (p_OCIE1A)
		{
			s_OCI1ACallback = p_callback;
			TIMSK1 |= _BV(OCIE1A);
		}
		else
		{
			s_OCI1BCallback = p_callback;
			TIMSK1 |= _BV(OCIE1B);
		}
	}
	else
	{
		if (p_OCIE1A)
		{
			TIMSK1 &= ~_BV(OCIE1A);
			s_OCI1ACallback = 0;
		}
		else
		{
			TIMSK1 &= ~_BV(OCIE1B);
			s_OCI1BCallback = 0;
		}
	}
}


void Timer1::setOverflow(bool p_enable, Callback p_callback)
{
	RC_TRACE("set overflow enable: %d Callback: %p", p_enable, p_callback);
	if (p_enable)
	{
		s_TOIE1Callback = p_callback;
		TIMSK1 |= _BV(TOIE1);
	}
	else
	{
		TIMSK1 &= ~_BV(TOIE1);
		s_TOIE1Callback = 0;
	}
}


void Timer1::setToggle(bool p_enable, bool p_OC1A)
{
	RC_TRACE("set toggle enable: %d OC1A: %d", p_enable, p_OC1A);
	if (p_enable)
	{
		TCCR1A |= p_OC1A ? _BV(COM1A0) : _BV(COM1B0);
	}
	else
	{
		TCCR1A &= p_OC1A ? ~_BV(COM1A0) : ~_BV(COM1B0);
	}
}

// namespace end
}


// Interrupt service routines

ISR(TIMER1_OVF_vect)
{
	if (s_TOIE1Callback != 0)
	{
		s_TOIE1Callback();
	}
}


ISR(TIMER1_COMPA_vect)
{
	if (s_OCI1ACallback != 0)
	{
		s_OCI1ACallback();
	}
}


ISR(TIMER1_COMPB_vect)
{
	if (s_OCI1BCallback != 0)
	{
		s_OCI1BCallback();
	}
}
