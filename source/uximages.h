#ifndef UXGRAPHICS_IMAGES_H
#define UXGRAPHICS_IMAGES_H

#include "uxgraphics.h"


typedef struct			{
	short pixelFormat;					// Pixel format
	short nElements;					// Number of entries
	void *data;							// (raw data) Color entries in their pixel format.
} UX_IMAGE_CLUT;

typedef struct UX_IMAGE_ANIM {
	int loop;
	int num;
	char *name;
	struct UX_IMAGE* img;
	int* frames;
	int* interv;
} UX_IMAGE_ANIM;

/* Image / Texture abstraction */
typedef struct UX_IMAGE {
	int x, y;						                    // Actual position of the image.
	int w, h;					                    	// Image dimensions.
	int sw, sh;											// Last image dimensions used for blitting.
	int sysw, sysh;										// nextpow2 size.
	int realw, realh;									// internal imagesize.
	float u0, v0, u1, v1;								// u,v textura [texscale]
	int bx,by,bz;										// Blit center
	int cx,cy,cz;							            // Rotation center
	int ax, ay, az;							            // Rotation angle
	unsigned int frameX, frameY;						// Frame size.
	float vU, vY;										// Scroll-type animation velocities.
	unsigned int cachePos;								// data position. (ram/vram (psp), texnumber (wii), unused otherwise)
	
	struct {
		int animated: 3;								// Animated? 0: NO, 1: STATIC, 2:DYNAMIC, 3: SCROLL
		int playing : 1;								// Animation playing
		int loop : 1;									// Animation loop
		int cached : 1;									// Image cached.
		int mipmapped: 1;								// Image mipmapped.
		int hLOD : 4;									// horizontal level of detail.
		int vLOD : 4; 									// vertical level of detail.
		int antialias: 1;								// Antialiased.
		int hREP : 3;									// horizontal repetition ( 0: Limit, 1: repeat, 2: mirror )
		int vREP : 3; 									// vertical repetition.
		int reserved;	         						// ------ 6-bit Unused.
	};
	
	unsigned int animSize;								// Number of animations.
	unsigned int curAnim;								// Current animation.
	UX_IMAGE_ANIM* anim;								// Array of animations.
	
	UX_IMAGE_CLUT pallete;								// Image pallette.
	unsigned int dataSize;								// raw data size.
	void *ptr;											// raw data image.
} UX_IMAGE;


/* Exports */
extern UX_IMAGE *uximages_loadimage(char *file);
extern void uximages_blitimage(UX_IMAGE *img);
extern void uximages_transferimage(UX_IMAGE *img);

#endif