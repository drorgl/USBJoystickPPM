#ifndef INC_RC_PPMOUT_H
#define INC_RC_PPMOUT_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** PPMOut.h
** Pulse Position Modulation Output functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include "rc_config.h"


namespace rc
{

/*! 
 *  \brief     Class to encapsulate PPM Output functionality.
 *  \details   This class provides a way to generate a PPM signal for a configurable amount of channels.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \warning   This class should <b>NOT</b> be used together with the standard Arduino Servo library,
 *             use rc::ServoOut instead.
 *  \copyright Public Domain.
 */
class PPMOut
{
public:
	
	/*! \brief Constructs a PPMOut object.
	    \param p_channels Number of active channels, <= RC_MAX_CHANNELS.*/
	PPMOut(uint8_t p_channels);
	
	/*! \brief Sets up timers and interrupts.
	    \param p_pin Pin to use as output pin, pins 9 and 10 are preferred and give the best result.
	    \param p_invert Invert the signal on true.
	    \note If precise timing is of importance then you should use either pin 9 or 10,
		      these can be toggled by the timer hardware and will give the best results. */
	void start(uint8_t p_pin, bool p_invert = false);
	
	/*! \brief Sets channel count
	    \param p_channels Channel count.*/
	void setChannelCount(uint8_t p_channels);
	
	/*! \brief Gets channel count.
	    \return The amount of active channels.*/
	uint8_t getChannelCount() const;
	
	/*! \brief Sets pulse length in microseconds.
	    \param p_length Pulse length in microseconds.*/
	void setPulseLength(uint16_t p_length);
	
	/*! \brief Gets pulse length in microseconds.
	    \return The current pulse length in microseconds.*/
	uint16_t getPulseLength() const;
	
	/*! \brief Sets pause length in microseconds.
	    \param p_length Pause length in microseconds.*/
	void setPauseLength(uint16_t p_length);
	
	/*! \brief Gets pause length in microseconds.
	    \return The current pause length in microseconds.*/
	uint16_t getPauseLength() const;
	
	/*! \brief Updates channel timings, will be sent at next frame.*/
	void update();
	
	/*! \brief Handles timer interrupt.*/
	static void handleInterrupt();
	
private:
	/*! \brief Update the entire timings buffer. */
	void updateTimings();
	
	/*! \brief Internal interrupt handling. */
	void isr();
	
	uint16_t m_pulseLength; //!< Pulse length in timer ticks.
	uint16_t m_pauseLength; //!< End of frame length in timer ticks.
	
	uint8_t m_channelCount;    //!< Number of active channels.
	
	volatile uint16_t m_channelTimings[RC_MAX_CHANNELS + 1]; //!< Timings per channel, in timer ticks.
	
	uint8_t   m_timingCount;                        //!< Number of active timings.
	uint8_t   m_timingPos;                          //!< Current position in timings buffer.
	uint16_t  m_timings[(RC_MAX_CHANNELS + 1) * 2]; //!< Timing values in timer ticks.
	
	uint8_t           m_mask; //!< Mask to use for pins other than 9 and 10
	volatile uint8_t* m_port; //!< Input port register for pins other than 9 and 10
	
	static PPMOut* s_instance; //!< Singleton instance
};
/** \example ppmout_example.pde
 * This is an example of how to use the PPMOut class.
 */

} // namespace end

#endif // INC_RC_PPMOUT_H
