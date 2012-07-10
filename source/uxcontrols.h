#ifndef UXCONTROLS_H
#define UXCONTROLS_H

#include "uxcontrols/psp.h"
#include "uxcontrols/nds.h"
#include "uxcontrols/win.h"
//#include "uxcontrols/ps3.h"	to-do.
#include "uxcontrols/wii.h"


/**
 ** Control structs.
 **/
typedef struct UX_CONTROLS {
#if defined(PSP)
	UXCONTROLS_PSPPAD    psppad;		//!< PSP controls.
#elif defined(_WIN32)
	UXCONTROLS_MOUSE     mouse;			//!< Mouse controls.
	UXCONTROLS_KEYBOARD  keyboard;		//!< Keyboard controls.
#elif defined(WII)
	UXCONTROLS_WIIMOTE   wiimotes[4];	//!< Wii controls.
#elif defined(NDS)
	UXCONTROLS_NDSPAD    ndspad;		//!< NDS controls.
#endif
} UX_CONTROLS;


/**
 ** Control functions.
 **/
extern UX_CONTROLS controls;			//!< Global object controls.
extern int uxcontrols_init();			//!< Initializate controls.
extern void uxcontrols_shutdown();		//!< Deinit controls.
extern void uxcontrols_read();			//!< Take a read.

#endif