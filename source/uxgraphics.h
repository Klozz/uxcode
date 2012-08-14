/*
 * uxgraphics.h
 * This file is used to manage graphics subsystem in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#ifndef UXGRAPHICS_H
#define UXGRAPHICS_H
/**
 \section GRAPHICS
*/

/** Full precise 2D vector / dot / position. */
typedef struct { 
	float x;	//!< X position
	float y;	//!< Y position
} UX_VECTOR2D;

/** Full precise 3D vector / dot / position. */
typedef struct { 
	float x;	//!< X position
	float y;	//!< Y position
	float z;	//!< Z position
} UX_VECTOR3D;

/** Fast 2D vector / dot / position */
typedef struct { 
	short x;	//!< X position
	short y;	//!< Y position
} UX_FVECTOR2D;

/** Fast 3D vector / dot / position */
typedef struct {
	short x;	//!< X position
	short y;	//!< Y position
	short z;	//!< Z position
} UX_FVECTOR3D;

/** Camera position and direction. The camera is positioned at *pos* looking at *look* and having at it's top *up*. */
typedef struct {
	UX_VECTOR3D pos;	//!< Camera position.
	UX_VECTOR3D up;		//!< Camera ceil vector.
	UX_VECTOR3D look;	//!< Camera looking at this point.
} UX_CAMERA3D;

/** A 2D integer box. */
typedef struct { 
	unsigned int x;		//!< X position of the top left corner.
	unsigned int y;		//!< Y position of the top left corner.
	unsigned int w;		//!< Width of the box.
	unsigned int h;		//!< Height of the box.
} UX_INTBOX;


#include "uxgraphics/psp.h"
#include "uxgraphics/nds.h"
#include "uxgraphics/win.h"
#include "uxgraphics/wii.h"
	
#include "uxvertex.h"
#include "uximages.h"

enum UX_PIXELFORMAT {
	UX_PF_5650,					//!< 16 bits, 5 bits per component, except green which has 6, no alpha.	texture, display, pallete
	UX_PF_5551,					//!< 15 bits, 5 bits per component, 1 alpha bit. texture, display, pallete
	UX_PF_4444,					//!< 12 bits, 4 bits per component, 4 alpha bits. texture, display, pallete
	UX_PF_6666,					//!< 24 bits, 6 bits per component
	UX_PF_8880,					//!< 24 bits, 8 bits per component, no alpha
	UX_PF_8888,					//!< 32 bits, 8 bits per component, 8 alpha bits. texture, display, pallete
	UX_PF_2BIT,					//!< 2 color palleted.
	UX_PF_4BIT,					//!< Paletted format, 4 bits (16 colors). texture
	UX_PF_8BIT,					//!< Paletted format, 8 bits (256 colors). texture
	UX_PF_DXT1,					//!< DXT1 compressed. texture
	UX_PF_DXT3,					//!< DXT3 compressed. texture
	UX_PF_DXT5					//!< DXT5 compressed. texture
};
	
/** Graphics initialize structure */
typedef struct UX_GRAPHICSMODE {
	unsigned int width;						//!< Graphics mode / window mode width, if needed.
	unsigned int height;					//!< Graphics mode / window mode height, if needed.
	unsigned int w_width;
	unsigned int w_height;
	enum UX_PIXELFORMAT pixelFormat;		//!< Graphics pixelformat, if needed.
	unsigned int extras;					//!< Extra-per-platform flags.
} UX_GRAPHICSMODE;

/** Render configuration structure. */
typedef struct UX_RENDER {
	UXCOLOR clear_color;					//!< Drawbuffer clear color.
	unsigned int clear_depth; 				//!< Clear depth (24bit) : 0x000000-0xffffff
	
	int faceculling_enabled;				//!< Hide reversed faces.
	int depthtest_enabled;					//!< Draw only if *depth* test passes.
	int texture3d_enabled;					//!< Textures in 3D mode enabled.
	int texture2d_enabled;					//!< Textures in 2D mode enabled.
	int blending_enabled;					//!< Blend function enabled.
	
	int faceculling;						//!< Polygon draw rotation: UX_GL_CULLBACK (clockwise), UX_GL_CULLFRONT (counter-clockwise).
	
	int depthtest_writes;					//!< Depth test writes.
	int depthtest_function;					//!< Depth test function.
	
	int alphatest_enabled;					//!< Draw only if *alpha* test passes.
	int alphatest_reference;				//!< Alpha test reference value: 0x00-0xFF
	int alphatest_operator;					//!< Alpha test operator: >,>=,<,<=,!=,==,1,0
	
	int blending_operator;					//!< Blend function operator:  +,-,max(),min()...
	int blending_src_function;				//!< Blend source color function
	int blending_dst_function;				//!< Blend destination color function
	int blending_logic;						//!< Blend logic operation &,|,~...
	
	int shade_model;
	
	int scissor_enabled;					//!< Scissoring enabled
	UX_INTBOX scissor_box;					//!< Scissor box: {x,y,w,h}
} UX_RENDER;

/* Viewport configuration structure. */
typedef struct UX_VIEWPORT {
	unsigned int sync;					//!< Video syncing (wait for scanlines).
	UX_INTBOX window;					//!< Screen box.
	//unsigned int width;					//!< Screen width 
	//unsigned int height;				//!< Screen height
	//unsigned int x;						//!< UNDOC x
	//unsigned int y;						//!< UNDOC y
	unsigned int _near;					//!< UNDOC near
	unsigned int _far;					//!< UNDOC far
	struct { float fovy; float aspect; float _near; float _far; } perspective3D;
	struct { float left; float right; float bottom; float top; float _near; float _far; } ortho2D;
	UX_MATRIX proypers;				/* precarga proyeccion perspectiva */
	UX_MATRIX proyort3;				/* precarga proyeccion ortogonal 3D */
	UX_MATRIX proyort2;				/* precarga proyeccion ortogonal 2D */
	UX_MATRIX view;					/* precarga matriz vista */
	UX_MATRIX modelview;			/* precarga a identidad */
	UX_CAMERA3D	cam3;				/* camara 3D activa */
} UX_VIEWPORT;


/*************************
 * Global variables      *
 *************************/
/** \internal */
extern int uxgraphics_inited;
extern int uxgraphics_in3D;

extern void *framebuffers[2];		//!< framebuffers.	(2? we need a define, cause NDS has 2 displays * 2 buffers = 4 framebuffers perhaps)
extern int fb;						//!< current framebuffer
/** \internal  */

extern UX_IMAGE		dispBuffer;		//!< Display buffer abstraction to image.
extern UX_IMAGE		drawBuffer;		//!< Draw buffer abstraction to image.
extern UX_RENDER	dRender;		//!< Current active render.
extern UX_VIEWPORT	dView;			//!< Current active viewport.
extern UX_GRAPHICSMODE graphics_mode; //!< Graphics init mode.

/*************************
 * Functions             *
 *************************/
extern int uxgraphics_init(UX_GRAPHICSMODE * window);		//!< Initialize graphics subsystem
extern void uxgraphics_shutdown();	//!< Deinitialize graphics subsytem

extern int uxgraphics_nearestPixelFormat(enum UX_PIXELFORMAT pf);

extern void uxgraphics_setViewMode(UX_VIEWPORT view /*!< [in] vie */, int force2D, int force3D);
extern void uxgraphics_setViewport(UX_VIEWPORT view, int mode);
extern void uxgraphics_viewmatrix(UX_VIEWPORT view, int mode);
extern void uxgraphics_modelmatrix();

extern void uxgraphics_setRenderMode(UX_RENDER render);

extern void uxgraphics_clearscreen();
extern void uxgraphics_flipscreen();

extern void uxgraphics_renderListMalloc(int size);

#endif