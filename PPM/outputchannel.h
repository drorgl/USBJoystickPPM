#ifndef INC_RC_OUTPUTCHANNEL_H
#define INC_RC_OUTPUTCHANNEL_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** outputchannel.h
** Place where outgoing channel data is stored
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include "rc_config.h"


/*!
 *  \file      outputchannel.h
 *  \brief     Outgoing channel data include file.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
*/

namespace rc
{
	enum OutputChannel //! OutputChannel index
	{
		OutputChannel_1,  //!< Output Channel 1
		OutputChannel_2,  //!< Output Channel 2
		OutputChannel_3,  //!< Output Channel 3
		OutputChannel_4,  //!< Output Channel 4
#if RC_MAX_CHANNELS >= 5
		OutputChannel_5,  //!< Output Channel 5
#endif
#if RC_MAX_CHANNELS >= 6
		OutputChannel_6,  //!< Output Channel 6
#endif
#if RC_MAX_CHANNELS >= 7
		OutputChannel_7,  //!< Output Channel 7
#endif
#if RC_MAX_CHANNELS >= 8
		OutputChannel_8,  //!< Output Channel 8
#endif
#if RC_MAX_CHANNELS >= 9
		OutputChannel_9,  //!< Output Channel 9
#endif
#if RC_MAX_CHANNELS >= 10
		OutputChannel_10, //!< Output Channel 10
#endif
#if RC_MAX_CHANNELS >= 11
		OutputChannel_11, //!< Output Channel 11
#endif
#if RC_MAX_CHANNELS >= 12
		OutputChannel_12, //!< Output Channel 12
#endif
#if RC_MAX_CHANNELS >= 13
		OutputChannel_13, //!< Output Channel 13
#endif
#if RC_MAX_CHANNELS >= 14
		OutputChannel_14, //!< Output Channel 14
#endif
#if RC_MAX_CHANNELS >= 15
		OutputChannel_15, //!< Output Channel 15
#endif
#if RC_MAX_CHANNELS >= 16
		OutputChannel_16, //!< Output Channel 16
#endif
#if RC_MAX_CHANNELS >= 17
		OutputChannel_17, //!< Output Channel 17
#endif
#if RC_MAX_CHANNELS >= 18
		OutputChannel_18, //!< Output Channel 18
#endif
		
		OutputChannel_Count,
		OutputChannel_None //!< No output channel, special case
	};
	
	
	/*! \brief Sets value for a certain output channel.
	    \param p_channel Output to set value of.
	    \param p_value Value to set in microseconds, range [750 - 2250].*/
	void setOutputChannel(OutputChannel p_channel, uint16_t p_value);
	
	/*! \brief Gets value of a certain output channel.
	    \param p_channel Output channel to get value of.
	    \return value of the channel in microseconds, range [750 - 2250].*/
	uint16_t getOutputChannel(OutputChannel p_channel);
	
	/*! \brief Gets a pointer to the raw output channels buffer.
	    \return Pointer to output channels buffer.*/
	uint16_t* getRawOutputChannels();
}

#endif // INC_RC_OUTPUTCHANNEL_H
