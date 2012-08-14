/*
 * uxcontrols/nds.h
 * This file is used to manage controls and keyboards subsystem for NDS in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#if defined(NDS)
/* NDS buttons */
typedef struct UXCONTROLS_NDSPAD_KEYS {
  	struct {
		unsigned int A       : 1;
		unsigned int B       : 1;
		unsigned int select  : 1;
		unsigned int start   : 1;
		unsigned int right   : 1;
		unsigned int left    : 1;
		unsigned int up      : 1;
		unsigned int down    : 1;
		unsigned int R       : 1;
		unsigned int L       : 1;
		unsigned int X       : 1;
		unsigned int Y       : 1;
		unsigned int touch   : 1;
		unsigned int lid     : 1;
		unsigned int unused  : 18;
	};
} UXCONTROLS_NDSPAD_KEYS;
 
/* NDS touch data */
typedef struct UXCONTROLS_NDSPAD_TOUCH {
	unsigned short rawx;
	unsigned short rawy;
	unsigned short x;				// Pixel x
	unsigned short y;				// Pixel y
	unsigned short z1;				// Crossresistance
	unsigned short z2;				// Crossresistance
} UXCONTROLS_NDSPAD_TOUCH;
 
/* NDS PAD definition */
typedef struct UXCONTROLS_NDSPAD {
	struct UXCONTROLS_NDSPAD_KEYS	held;		//! Keys currently held.
	struct UXCONTROLS_NDSPAD_KEYS	pressed;	//! Keys inmediately pressed.
	struct UXCONTROLS_NDSPAD_KEYS	released;	//! Keys inmediately released.
 
	struct UXCONTROLS_NDSPAD_TOUCH  touch;
} UXCONTROLS_NDSPAD;
#endif