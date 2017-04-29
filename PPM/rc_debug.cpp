/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** rc_debug.cpp
** Debugging functions
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <stdio.h>

#include "rc_debug.h"


#if RC_GLOBAL_LEVEL > 0
namespace rc
{

void halt(const prog_char* p_file, uint16_t p_line, const prog_char* p_fmt, ...)
{
	fprintf_P(stdout, PSTR("ASSERT FAILED at %S:%d: "), p_file, p_line);
	
	va_list vlist;
	va_start(vlist, p_fmt);
	vfprintf_P(stdout, p_fmt, vlist);
	va_end(vlist);
	
	fprintf_P(stdout, PSTR("\n"));
	for (;;) {}
}


void error(const prog_char* p_file, uint16_t p_line, const prog_char* p_fmt, ...)
{
	fprintf_P(stdout, PSTR("[ERROR] %S:%d: "), p_file, p_line);
	
	va_list vlist;
	va_start(vlist, p_fmt);
	vfprintf_P(stdout, p_fmt, vlist);
	va_end(vlist);
	
	fprintf_P(stdout, PSTR("\n"));
}


void warn(const prog_char* p_file, uint16_t p_line, const prog_char* p_fmt, ...)
{
	fprintf_P(stdout, PSTR("[WARN] %S:%d: "), p_file, p_line);
	
	va_list vlist;
	va_start(vlist, p_fmt);
	vfprintf_P(stdout, p_fmt, vlist);
	va_end(vlist);
	
	fprintf_P(stdout, PSTR("\n"));
}


void info(const prog_char* p_file, uint16_t p_line, const prog_char* p_fmt, ...)
{
	fprintf_P(stdout, PSTR("[INFO] %S:%d: "), p_file, p_line);
	
	va_list vlist;
	va_start(vlist, p_fmt);
	vfprintf_P(stdout, p_fmt, vlist);
	va_end(vlist);
	
	fprintf_P(stdout, PSTR("\n"));
}


void debug(const prog_char* p_file, uint16_t p_line, const prog_char* p_fmt, ...)
{
	fprintf_P(stdout, PSTR("[DEBUG] %S:%d: "), p_file, p_line);
	
	va_list vlist;
	va_start(vlist, p_fmt);
	vfprintf_P(stdout, p_fmt, vlist);
	va_end(vlist);
	
	fprintf_P(stdout, PSTR("\n"));
}


void trace(const prog_char* p_file, uint16_t p_line, const prog_char* p_fmt, ...)
{
	fprintf_P(stdout, PSTR("[TRACE] %S:%d: "), p_file, p_line);
	
	va_list vlist;
	va_start(vlist, p_fmt);
	vfprintf_P(stdout, p_fmt, vlist);
	va_end(vlist);
	
	fprintf_P(stdout, PSTR("\n"));
}


// namespace end
}
#endif // RC_GLOBAL_LEVEL > 0
