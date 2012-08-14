/*
 * uxcontrols/psp.h
 * This file is used to manage controls and keyboards subsystem for PlayStationPortable in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#if defined(PSP)
/* PSP buttons */
typedef struct UXCONTROLS_PSPPAD_KEYS {
	struct {
		unsigned int select  : 1;
		unsigned int unknwn  : 2;               //!< two unknown bits
		unsigned int start   : 1;
		unsigned int up      : 1;
		unsigned int right   : 1;
		unsigned int down    : 1;
		unsigned int left    : 1;
		unsigned int L       : 1;
		unsigned int R       : 1;
		unsigned int unknw2  : 2;	            //!< two unknown bits
		unsigned int triangle: 1;
		unsigned int circle  : 1;
		unsigned int cross   : 1;
		unsigned int square  : 1;
		unsigned int home    : 1;               //!< Need kernel access
		unsigned int hold    : 1;
		unsigned int wlanup  : 1;               //!< Need kernel access
		unsigned int remote  : 1;               //!< Need kernel access
		unsigned int volup   : 1;               //!< Need kernel access
		unsigned int voldown : 1;               //!< Need kernel access
		unsigned int screen  : 1;               //!< Need kernel access
		unsigned int note    : 1;               //!< Need kernel access
		unsigned int disc    : 1;               //!< Need kernel access
		unsigned int ms      : 1;               //!< Need kernel access
	};
} UXCONTROLS_PSPPAD_KEYS;

/* PSP definition */
typedef struct UXCONTROLS_PSPPAD {
	struct UXCONTROLS_PSPPAD_KEYS	held;       //!< Keys currently held.
	struct UXCONTROLS_PSPPAD_KEYS	pressed;    //!< Keys inmediately pressed.
	struct UXCONTROLS_PSPPAD_KEYS	released;   //!< Keys inmediately released.

	unsigned char analogToDpadSensitivity;      //!< Sensitivity to convert from analog to digital. (0, disabled)
	unsigned char analogMinSensitivity;         //!< Absolute minimum value to store analog.

	signed char analogX;                        //!< Analog x position (-128: left, +127: right)
	signed char analogY;                        //!< Analog y position (-128: up, +127: down)
} UXCONTROLS_PSPPAD;
#endif