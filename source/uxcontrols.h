#ifndef UXCONTROLS_H
#define UXCONTROLS_H

#include "uxcontrols/psp.h"
#include "uxcontrols/nds.h"
#include "uxcontrols/win.h"
//#include "uxcontrols/ps3.h"	to-do.
#include "uxcontrols/wii.h"


/**
 ** Control struct.
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


extern UX_CONTROLS controls;			//!< Global object controls.
extern int uxcontrols_inited;
extern int uxcontrols_init();
extern int uxcontrols_shutdown();
extern int uxcontrols_read();

#endif