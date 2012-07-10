#if defined(WII)

//#include "wpad_leds.h"	//led hack
//#include "__wpads.h"

/* Wii Guitar */
typedef struct UXCONTROLS_WIIEXPANSION_GUITARHERO {
	unsigned short strumDown : 1;
	unsigned short reserved3 : 1;
	unsigned short minus     : 1;
	unsigned short plus      : 1;
	unsigned short reserved2 : 2;
	unsigned short orange    : 1;
	unsigned short red       : 1;
	unsigned short blue      : 1;
	unsigned short green     : 1;
	unsigned short yellow    : 1;
	unsigned short reserved  : 2;
	unsigned short strumUp   : 1;
} UXCONTROLS_WIIEXPANSION_GUITARHERO;

/* Wii GameCube */
typedef struct UXCONTROLS_WIIGAMECUBE_BUTTONS {
	unsigned short reserved2 : 3;
	unsigned short start     : 1;
	unsigned short y         : 1;
	unsigned short x         : 1;
	unsigned short b         : 1;
	unsigned short a         : 1;
	unsigned short reserved  : 1;
	unsigned short l         : 1;
	unsigned short r         : 1;
	unsigned short z         : 1;
	unsigned short up        : 1;
	unsigned short down      : 1;
	unsigned short right     : 1;
	unsigned short left      : 1;
} UXCONTROLS_WIIGAMECUBE_BUTTONS;

/* Wii Nunchuk */
typedef struct UXCONTROLS_WIIEXPANSION_NUNCHUCK {
	unsigned short           : 14;									
	unsigned short c         : 1;									
	unsigned short z         : 1;									
} UXCONTROLS_WIIEXPANSION_NUNCHUCK;

/* Wii Classic */
typedef struct UXCONTROLS_WIIEXPANSION_CLASSIC {
	unsigned short right     : 1;
	unsigned short down      : 1;
	unsigned short l         : 1;
	unsigned short minus     : 1;
	unsigned short home      : 1;
	unsigned short plus      : 1;
	unsigned short r         : 1;
	unsigned short reserved  : 1;
	unsigned short zl        : 1;
	unsigned short b         : 1;
	unsigned short y         : 1;
	unsigned short a         : 1;
	unsigned short x         : 1;	
	unsigned short zr        : 1;
	unsigned short left      : 1;
	unsigned short up        : 1;
} UXCONTROLS_WIIEXPANSION_CLASSIC;

/* Wiimote + expansion buttons */
typedef struct UXCONTROLS_WIIMOTE_BUTTONS { 
	/* expansion */
	union UXCONTROLS_WIIEXPANSION {
		struct UXCONTROLS_WIIEXPANSION_CLASSIC    classic;
		struct UXCONTROLS_WIIEXPANSION_NUNCHUCK   nunchuck;
		struct UXCONTROLS_WIIEXPANSION_GUITARHERO guitar;
	} expansion;
	
	// Wiimote.
	struct {
		unsigned short reserved2 : 3;
		unsigned short plus      : 1;
		unsigned short up        : 1;
		unsigned short down      : 1;
		unsigned short right     : 1;
		unsigned short left      : 1;
		unsigned short home      : 1;
		unsigned short reserved  : 2;
		unsigned short minus     : 1;
		unsigned short a         : 1;
		unsigned short b         : 1;
		unsigned short one       : 1;
		unsigned short two       : 1;
	};
} UXCONTROLS_WIIMOTE_BUTTONS;

/* typedefs */
#define UXCONTROLS_WII_ACCELS		vec3w_t
#define UXCONTROLS_WII_ORIENTATION 	struct orient_t
#define UXCONTROLS_WII_GFORCE 		gforce_t
typedef ir_t UXCONTROLS_WII_IR;

/* Wiimote definition */
typedef struct UXCONTROLS_WIIMOTE {
	UXCONTROLS_WII_ACCELS       wmAccels;      // Accels.
	UXCONTROLS_WII_ORIENTATION  wmOrientation; // Orientations.
	UXCONTROLS_WII_GFORCE       wmGforce;      // Gravity forces.
	UXCONTROLS_WII_IR           wmIr;          // Infrared.
	
	UXCONTROLS_WIIMOTE_BUTTONS	wmpressed;     // Wiimote keys inmediately pressed
	UXCONTROLS_WIIMOTE_BUTTONS	wmreleased;    // Wiimote keys inmediately released
	UXCONTROLS_WIIMOTE_BUTTONS	wmheld;        // Wiimote keys currently held.
	
	UXCONTROLS_WIIGAMECUBE_BUTTONS gcpressed;  // Gamecube keys inmediately pressed
	UXCONTROLS_WIIGAMECUBE_BUTTONS gcreleased; // Gamecube keys inmediately released
	UXCONTROLS_WIIGAMECUBE_BUTTONS gcheld;     // Gamecube keys currently held.
	
	unsigned short gcAnalogL, gcAnalogR;       // Gamecube: L, R.
	signed short gcLAnalogX, gcLAnalogY;       // Gamecube: Analog Left.
	signed short gcRAnalogX, gcRAnalogY;       // Gamecube: Analog Right.
	
	expansion_t expansion;                     // Expansion type.
	
	unsigned short batt;                       // Battery level.
	unsigned char isViewing;                   // Seeing the sensor-bar.
} UXCONTROLS_WIIMOTE;


extern void uxcontrols_wiiread(UXCONTROLS_WIIMOTE *wiimote, int i);
#endif