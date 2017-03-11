// -----------------------------------------------------------------------------
// MXM LIBRARY
// -----------------------------------------------------------------------------
// CONTRIBUTORS : MAXIME FONTAINE
// VERSION : 1.0
// DATE : 12/11/2016
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

// This file includes all classes, functions, variables and constants
// of the Apex Technologies Library 'capex'

#if __WIN32__
	#define MXM_CALL __fastcall
#elif __linux__
	#define MXM_CALL
#else
	#define MXM_CALL
#endif

#include "./array.h"
#include "./usb.h"
