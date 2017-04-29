#ifndef INC_RC_TIMER1_H
#define INC_RC_TIMER1_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Timer1.h
** Timer1 functionality
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>


namespace rc
{

/*! 
 *  \brief     Class to encapsulate Timer1 functions.
 *  \details   This class provides centralised Timer1 controls.
 *  \author    Daniel van den Ouden
 *  \date      Feb-2012
 *  \warning   This class should <b>NOT</b> be used together with the standard Arduino Servo library,
 *             use rc::ServoOut instead.
 *  \copyright Public Domain.
 */
class Timer1
{
public:
	typedef void (*Callback)(void); //!< Callback function for interrupt routines
	
	/*! \brief Sets all default values, call this first.
	    \param p_debug Whether or not to run at debug speed (/256).
	    \note  This function should be called prior to using any other Timer1 function.*/
	static void init(bool p_debug = false);
	
	/*! \brief Starts timer1.*/
	static void start();
	
	/*! \brief Checks if timer1 is running.
	    \return Whether or not timer1 is running.*/
	static bool isRunning();
	
	/*! \brief Stops timer1.*/
	static void stop();
	
	/*! \brief Enables/Disables Compare Match Interrupt.
	    \param p_enable Whether to enable or disable Compare Match Interrupt.
	    \param p_OCIE1A Whether to use OCIE1A or OCIE1B.
	    \param p_callback Function to call at interrupt.*/
	static void setCompareMatch(bool p_enable, bool p_OCIE1A, Callback p_callback = 0);
		
	/*! \brief Enables/Disables Overflow Interrupt.
	    \param p_enable Whether to enable or disable Overflow Interrupt.
	    \param p_callback Function to call at interrupt.*/
	static void setOverflow(bool p_enable, Callback p_callback = 0);
	
	/*! \brief Enables/Disables Toggle pin on Compare Match A.
	    \param p_enable Whether to enable or disable toggle pin.
	    \param p_OC1A Whether to toggle OC1A or OC1B.*/
	static void setToggle(bool p_enable, bool p_OC1A);
	
	
private:
	Timer1(); //!< Not instantiable
	
};
/** \example timer1_example.pde
 * This is an example of how to use the Timer1 class.
 */


} // namespace end

#endif // INC_RC_TIMER1_H
