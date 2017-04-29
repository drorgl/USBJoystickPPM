#ifndef INC_RC_DEBUG_LIB_H
#define INC_RC_DEBUG_LIB_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** rc_debug_lib.h
** Internal header file for debugging, do NOT include this in your own project
** Changes in this file will cause a rebuild of the entire lib
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

// This is the library debug level
#define RC_LIB_LEVEL 0
// 0 = OFF - asserts disabled
// 1 = ERROR - Asserts enabled
// 2 = WARN  - Warnings enabled
// 3 = INFO  - Informational messages enabled
// 4 = DEBUG - Debugging messages enabled
// 5 = TRACE - Trace messages enabled

#include "rc_config.h"

// check if debugging is enabled, if so, overrule the debug level
#if RC_GLOBAL_LEVEL > 0
#undef RC_DEBUG_LEVEL
#define RC_DEBUG_LEVEL RC_LIB_LEVEL
#endif

// include the actual debug header
#include "rc_debug.h"


#endif // INC_RC_DEBUG_LIB_H
