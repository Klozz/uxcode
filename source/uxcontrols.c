/*
 * uxcontrols.c
 * This file is used to manage controls and keyboards subsystem in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */
#include "utils.h"		// Global common utils

UX_CONTROLS controls;
int uxcontrols_inited = false;


/** @defgroup ux_controls Controls

	Input routines.
	@{
*/

/** 
	\brief Initialize the controls subsystem.
	\return 0 on success, failed otherwise.
*/
int uxcontrols_init() {
	if (uxcontrols_inited == true) { return false; }
	
	#if defined(PSP)
		sceCtrlSetSamplingCycle(0);
		sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
		uxcontrols_inited = true;
	#elif defined(WII)
		WPAD_Init();
		PAD_Init();
		WPAD_SetVRes(-1, rmode->fbWidth, rmode->efbHeight); // IR-resolution
		WPAD_SetDataFormat(WPAD_CHAN_ALL, WPAD_FMT_BTNS_ACC_IR);
		WPAD_SetIdleTimeout(300); // 5 mins
		uxcontrols_inited = true;
	#endif
	
	return !(uxcontrols_inited == true);
}

/**
	\brief De-initialize the controls subsystem
	\return 0 on success, failed otherwise.
*/
int uxcontrols_shutdown() {
	if (uxcontrols_inited == false) { return false; }
	
	#if defined(WII)
		WPAD_SetIdleTimeout(1);  // Let all turn off now.
		WPAD_Shutdown();         // Finalize wpad
	#endif
	
	uxcontrols_inited = false;
	
	return !(uxcontrols_inited == false);
}


/** 
 * \brief Take a read of the current input state.
 * \todo
		- Maybe include auto-repeat system.
		- PS3 platform-dependant code.
		- Wii accel calibration
		- Wii led hack?
 * \return 0 on success, failed otherwise.	
 */
int uxcontrols_read() {
	#if defined(PSP)
		unsigned int* pheld;
		unsigned int* ppressed;
		unsigned int* preleased;

		/* Read */
		SceCtrlData ctl;
		sceCtrlPeekBufferPositive(&ctl,1);	

		/* Compute press & release */
		pheld     = (unsigned int*)(&controls.psppad.held);
		ppressed  = (unsigned int*)(&controls.psppad.pressed);
		preleased = (unsigned int*)(&controls.psppad.released);

		/* Store readings */
		*ppressed = ~(*pheld) & ctl.Buttons;
		*preleased = *pheld & ~ctl.Buttons;
		*pheld = ctl.Buttons;
	#elif defined(_WIN32)
		// This is better placed ... in screenflip?
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) { ux_quit = TRUE; }
			else { TranslateMessage (&msg); DispatchMessage (&msg); }
		}
	#elif defined(WII)
		/* Do readings */
		WPAD_ScanPads();
		PAD_ScanPads();
		
		/* Store values */
		uxcontrols_wiiread( &(controls.wiimotes[0]), 0 );
		uxcontrols_wiiread( &(controls.wiimotes[1]), 1 );
		uxcontrols_wiiread( &(controls.wiimotes[2]), 2 );
		uxcontrols_wiiread( &(controls.wiimotes[3]), 3 );
	#elif defined(NDS)
		unsigned int* keys;
		scanKeys();
		
		touchRead((touchPosition *) &(controls.ndspad.touch));
		keys = (unsigned int *)( &(controls.ndspad.held) );	    *keys = keysHeld();
		keys = (unsigned int *)( &(controls.ndspad.pressed) );	*keys = keysDown();
		keys = (unsigned int *)( &(controls.ndspad.released) );	*keys = keysUp();
	#endif
	return 0;
}

/** @} */

#if defined(WII)
//#define __WPADS_ADDR 0x0				// led hack

void uxcontrols_wiiread(UXCONTROLS_WIIMOTE *wiimote, int i) {
	
	//#define	UXCONTROLS_WIILED_RESET for (j=0;j<4;j++) { if (i==j) { wleds[i][j] = 1; } else { wleds[i][j] = 0; } }
	#define UXCONTROLS_WIILED_RESET
	
	//struct wiimote_t ** __wpads = *((struct wiimote_t ***) __WPADS_ADDR);			//led hack
	unsigned int* keys;
	unsigned short* keyss;

	wiimote->batt		= WPAD_BatteryLevel(i);
	if (wiimote->batt<=0) { 
		uxmemset(wiimote,0,sizeof(UXCONTROLS_WIIMOTE));
		UXCONTROLS_WIILED_RESET
		return;
	}
	
	keys = (unsigned int*)( &(wiimote->wmheld));        *keys = WPAD_ButtonsHeld(i);
	keys = (unsigned int*)( &(wiimote->wmpressed));     *keys = WPAD_ButtonsDown(i);
	keys = (unsigned int*)( &(wiimote->wmreleased));    *keys = WPAD_ButtonsUp(i);
	keyss = (unsigned short*)( &(wiimote->gcheld));     *keyss = PAD_ButtonsHeld(i);
	keyss = (unsigned short*)( &(wiimote->gcpressed));  *keyss = PAD_ButtonsDown(i);
	keyss = (unsigned short*)( &(wiimote->gcreleased)); *keyss = PAD_ButtonsUp(i);
	
	wiimote->gcAnalogL	= PAD_TriggerL(i);
	wiimote->gcAnalogR	= PAD_TriggerR(i);
	wiimote->gcLAnalogX	= PAD_StickX(i);
	wiimote->gcLAnalogY	= -PAD_StickY(i);
	wiimote->gcRAnalogX	= PAD_SubStickX(i);
	wiimote->gcRAnalogY	= -PAD_SubStickY(i);
	
	WPAD_IR(i,&(wiimote->wmIr));
	WPAD_Expansion(i,&(wiimote->expansion));
	WPAD_Orientation(i,&(wiimote->wmOrientation));
	WPAD_GForce(i,&(wiimote->wmGforce));
	WPAD_Accel(i,&(wiimote->wmAccels));
	
	wiimote->isViewing				= wiimote->wmIr.num_dots;
	wiimote->wmOrientation.pitch	= -wiimote->wmOrientation.pitch;
		
	/* CALIBRACION ACCEL */
	//wiimote[i]->wmAccels.x = wiimote[i]->wmAccels.x - __wpads[i]->accel_calib.cal_zero.x;
	//wiimote[i]->wmAccels.y = -(wiimote[i]->wmAccels.y - __wpads[i]->accel_calib.cal_zero.y);
	//wiimote[i]->wmAccels.z = wiimote[i]->wmAccels.z - __wpads[i]->accel_calib.cal_zero.z;
		
	/* CALIBRACION GFORCE */
	//wiimote[i]->wmGforce.x = wiimote[i]->wmGforce.x - __wpads[i]->accel_calib.cal_g.x;
	//wiimote[i]->wmGforce.y = -(wiimote[i]->wmGforce.y - __wpads[i]->accel_calib.cal_g.y); // no estoy seguro
	//wiimote[i]->wmGforce.z = wiimote[i]->wmGforce.z - __wpads[i]->accel_calib.cal_g.z;
}
#endif

