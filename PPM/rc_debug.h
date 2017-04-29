#ifndef INC_RC_DEBUG_H
#define INC_RC_DEBUG_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** rc_debug.h
** Debugging functions and macros
** Changes in this file will cause a rebuild of the entire lib
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

// Include for program space related macros
#include <avr/pgmspace.h>

// add missing typedefs
typedef char PROGMEM prog_char;
typedef uint8_t PROGMEM prog_uint8_t;


// include global config settings first
#include "rc_config.h"

// sanity checking
#if RC_GLOBAL_LEVEL == 0 && RC_DEBUG_LEVEL > 0
	#error Attempt to use RC_DEBUG_LEVEL > 0 while RC_GLOBAL_LEVEL == 0, please change RC_GLOBAL_LEVEL first
#endif


// Define Asserts
#if RC_DEBUG_LEVEL >= 1
	#define RC_ASSERT(x) \
		do { if (!(x)) { rc::halt(PSTR(__FILE__), __LINE__, PSTR(#x)); } } while (0)
	#define RC_ASSERT_MSG(x, fmt, ...) \
		do { if (!(x)) { rc::halt(PSTR(__FILE__), __LINE__, PSTR(fmt), ##__VA_ARGS__); } } while (0)
	#define RC_ASSERT_MINMAX(x, min, max) \
		do { if ((x) > (max) || (x) < (min)) { rc::halt(PSTR(__FILE__), __LINE__, \
		PSTR("%S (%d) out of bounds [%d - %d]"), PSTR(#x), (x), (min), (max)); } } while (0)
#else
	#define RC_ASSERT(x)
	#define RC_ASSERT_MSG(x, fmt, ...)
	#define RC_ASSERT_MINMAX(x, min, max)
#endif

// Define Checks
#if RC_DEBUG_LEVEL >= 2
	#define RC_CHECK(x) \
		do { if (!(x)) { rc::warn(PSTR(__FILE__), __LINE__, PSTR("failed check: %S"), PSTR(#x)); } } while (0)
	#define RC_CHECK_MSG(x, fmt, ...) \
		do { if (!(x)) { rc::warn(PSTR(__FILE__), __LINE__, PSTR(fmt), ##__VA_ARGS__); } } while (0)
	#define RC_CHECK_MINMAX(x, min, max) \
		do { if ((x) > (max) || (x) < (min)) { rc::warn(PSTR(__FILE__), __LINE__, \
		PSTR("%S (%d) out of bounds [%d - %d]"), PSTR(#x), (x), (min), (max)); } } while (0)
#else
	#define RC_CHECK(x)
	#define RC_CHECK_MSG(x, fmt, ...)
	#define RC_CHECK_MINMAX(x, min, max)
#endif

// Define error printing
#if RC_DEBUG_LEVEL >= 1
	#define RC_ERROR(fmt, ...) \
		do { rc::error(PSTR(__FILE__), __LINE__, PSTR(fmt),  ##__VA_ARGS__); } while (0)
#else
	#define RC_ERROR(fmt, ...)
#endif

// Define warning printing
#if RC_DEBUG_LEVEL >= 2
	#define RC_WARN(fmt, ...) \
		do { rc::warn(PSTR(__FILE__), __LINE__, PSTR(fmt),  ##__VA_ARGS__); } while (0)
#else
	#define RC_WARN(fmt, ...)
#endif

// Define info printing
#if RC_DEBUG_LEVEL >= 3
	#define RC_INFO(fmt, ...) \
		do { rc::info(PSTR(__FILE__), __LINE__, PSTR(fmt),  ##__VA_ARGS__); } while (0)
#else
	#define RC_INFO(fmt, ...)
#endif

// Define debug printing
#if RC_DEBUG_LEVEL >= 4
	#define RC_DEBUG(fmt, ...) \
		do { rc::debug(PSTR(__FILE__), __LINE__, PSTR(fmt),  ##__VA_ARGS__); } while (0)
#else
	#define RC_DEBUG(fmt, ...)
#endif

// Define trace printing
#if RC_DEBUG_LEVEL >= 5
	#define RC_TRACE(fmt, ...) \
		do { rc::trace(PSTR(__FILE__), __LINE__, PSTR(fmt), ##__VA_ARGS__); } while (0)
#else
	#define RC_TRACE(fmt, ...)
#endif


// Define the debugging functions, only enable when debugging is in place
#if RC_GLOBAL_LEVEL > 0
namespace rc
{
	void halt(const prog_char* p_file, uint16_t p_line, const prog_char* p_fmt, ...);
	void error(const prog_char* p_file, uint16_t p_line, const prog_char* p_fmt, ...);
	void warn(const prog_char* p_file, uint16_t p_line, const prog_char* p_fmt, ...);
	void info(const prog_char* p_file, uint16_t p_line, const prog_char* p_fmt, ...);
	void debug(const prog_char* p_file, uint16_t p_line, const prog_char* p_fmt, ...);
	void trace(const prog_char* p_file, uint16_t p_line, const prog_char* p_fmt, ...);
}
#endif
/** \example debug_example.pde
 * This is an example of how to use the debug functions.
 */


#endif // INC_RC_DEBUG_H
