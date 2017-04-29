/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** PPMOut.cpp
** Pulse Position Modulation Output functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <Arduino.h>

#include "outputchannel.h"
#include "PPMOut.h"
#include "rc_debug_lib.h"
#include "Timer1.h"


namespace rc
{

PPMOut* PPMOut::s_instance = 0;


// Public functions

PPMOut::PPMOut(uint8_t p_channels)
:
m_pulseLength(500),
m_pauseLength(10500),
m_channelCount(p_channels),
m_timingCount((p_channels + 1) * 2)
{
	s_instance = this;
}


void PPMOut::start(uint8_t p_pin, bool p_invert)
{
	RC_TRACE("start pin: %u invert: %d", p_pin, p_invert);
	
	// stop timer 1
	rc::Timer1::stop();
	
	// Fill channelTimings buffer with data from channels buffer
	update();
	
	// Fill timings buffer with data from channelTimings buffer (set up a complete PPM frame)
	updateTimings();
	
	m_timingPos = p_invert ? 0 : 1;
	
	pinMode(p_pin, OUTPUT);
	
	// First disable the output compare match A interrupt
	rc::Timer1::setCompareMatch(false, true);
	
	// Configure timer1 Toggle OC1A/OC1B on Compare Match
	if (p_pin == 9 || p_pin == 10)
	{
		rc::Timer1::setToggle(true, p_pin == 9);
	}
	else
	{
		m_mask = digitalPinToBitMask(p_pin);
		uint8_t port = digitalPinToPort(p_pin);
		m_port = portInputRegister(port);
	}
	
	// set compare value
	OCR1A = TCNT1 + m_timings[p_invert ? m_timingCount - 1 : 0];
	
	// enable timer output compare match A interrupts
	rc::Timer1::setCompareMatch(true, true, PPMOut::handleInterrupt);
	
	// start the timer
	rc::Timer1::start();
}


void PPMOut::setChannelCount(uint8_t p_channels)
{
	RC_TRACE("set channel count %u", p_channels);
	RC_ASSERT_MINMAX(p_channels, 1, RC_MAX_CHANNELS);
	m_channelCount = p_channels;
}


uint8_t PPMOut::getChannelCount() const
{
	return m_channelCount;
}


void PPMOut::setPulseLength(uint16_t p_length)
{
	RC_TRACE("set pulse length %u us", p_length);
	RC_ASSERT_MINMAX(p_length, 0, 32766);
	
	m_pulseLength = p_length << 1;
}


uint16_t PPMOut::getPulseLength() const
{
	return m_pulseLength >> 1;
}


void PPMOut::setPauseLength(uint16_t p_length)
{
	RC_TRACE("set pause length %u us", p_length);
	RC_ASSERT_MINMAX(p_length, 0, 32766);
	
	m_pauseLength = p_length << 1;
}


uint16_t PPMOut::getPauseLength() const
{
	return m_pauseLength >> 1;
}


void PPMOut::update()
{
	const uint16_t* channels = getRawOutputChannels();
	for (uint8_t i = 0; i < m_channelCount; ++i)
	{
		m_channelTimings[i] = channels[i] << 1;
	}
}


void PPMOut::handleInterrupt()
{
	if (s_instance != 0)
	{
		s_instance->isr();
	}
}


// Private functions

void PPMOut::updateTimings()
{
	uint16_t* scratch = m_timings;
	
	// copy all pre-calculated timings
	for (uint8_t i = 0; i < m_channelCount; ++i)
	{
		// set pulse length
		*scratch = m_pulseLength;
		++scratch;
		
		// set timing
		*scratch = m_channelTimings[i] - m_pulseLength;
		++scratch;
	}
	
	// set final pulse length
	*scratch = m_pulseLength;
	++scratch;
	
	// set pause length
	*scratch = m_pauseLength - m_pulseLength;
	
	// update number of timings
	m_timingCount = (m_channelCount + 1) * 2;
}


void PPMOut::isr()
{
	// set the compare register with the next value
	OCR1A += m_timings[m_timingPos];
	
	// toggle pin, pins 9 and 10 will toggle themselves
	if (m_port != 0)
	{
		*m_port |= m_mask;
	}
	
	// update position
	++m_timingPos;
	if (m_timingPos >= m_timingCount)
	{
		m_timingPos = 0;
		
		// we're at the end of frame here, so there's plenty of time to update
		updateTimings();
	}
}

// namespace end
}
