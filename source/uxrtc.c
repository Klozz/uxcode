/*
 * uxrtc.c
 * This file is used to manage clock in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#include "utils.h"

#define FRAMES_UNTIL_CHECK 3

int uxrtc_inited 		= 0;

int uxrtc_framecount	= 0;
int uxrtc_framespsec	= 0;
int uxrtc_framesuchk	= FRAMES_UNTIL_CHECK;
UXTIMERTC uxrtc_tnext;
UXTIMERTC uxrtc_tcurr;

/** @defgroup ux_rtc RTC. Clock functions

@{
\brief Clock functions.
*/

 /**
  * \brief Clock initialization
  */
int uxrtc_init() {
	#ifdef PSP
		sceRtcGetCurrentTick(&uxrtc_tcurr);
		sceRtcTickAddSeconds(&uxrtc_tnext,&uxrtc_tcurr,1);
	#endif
	uxrtc_inited = 1;
	return 0;
}

 /**
  * \brief Current FPS.
  * Call this function once in a frame for fps calculation.
  */
int uxrtc_fps() {
	#ifdef PSP
	uxrtc_framecount++;
	uxrtc_framesuchk--;
	if (uxrtc_framesuchk == 0) {
		uxrtc_framesuchk = FRAMES_UNTIL_CHECK;
		sceRtcGetCurrentTick(&uxrtc_tcurr);
		if (sceRtcCompareTick(&uxrtc_tcurr,&uxrtc_tnext) >= 0) {
			sceRtcTickAddSeconds(&uxrtc_tnext,&uxrtc_tcurr,1);
			uxrtc_framespsec = uxrtc_framecount;
			uxrtc_framecount = 0;
		}
	}
	#endif
	return uxrtc_framespsec;
}


 /**
  * \brief Clock deinitialization
  */
void uxrtc_shutdown() {
	uxrtc_inited = 0;
}

/**
@}
*/