#ifndef UXGRAPHICS_H
#define UXGRAPHICS_H

typedef struct { float x, y; }                  UX_VECTOR2D;    //full precise vector 2d
typedef struct { float x, y, z; }               UX_VECTOR3D;    //full precise vector 3d
typedef struct { short x, y; }                  UX_FVECTOR2D;   //fast vector 2d
typedef struct { short x, y, z; }               UX_FVECTOR3D;   //fast vector 3d
typedef struct { UX_VECTOR3D pos, up, look; }   UX_CAMERA3D;    //camera coordinates
typedef struct { int x, y, w, h; }              UX_INTBOX;      //yeah, a box.


#include "uxgraphics/psp.h"
#include "uxgraphics/nds.h"
#include "uxgraphics/win.h"
#include "uxgraphics/wii.h"
	
#include "uxvertex.h"
#include "uximages.h"


/* Render-mode abstraction: */
typedef struct UX_RENDER {
	UXCOLOR clear_color;								// RGBA(r,g,b,a)
	unsigned int clear_depth; 							// 0x000000-0xffffff 24bit power.
	
	int faceculling_enabled;							// 1|0
	int depthtest_enabled;								// 1|0
	int texture3d_enabled;								// 1|0
	int texture2d_enabled;								// 1|0
	int blending_enabled;								// 1|0
	
	int faceculling;									// CW,CCW
	
	int depthtest_writes;								// 1|0
	int depthtest_function;								// >,>=,<,<=,!=,==,1,0
	
	int alphatest_enabled;								// 1|0
	int alphatest_reference;							// 0x00-0xFF
	int alphatest_operator;								// >,>=,<,<=,!=,==,1,0
	
	int blending_operator;								// +,-,max(),min()...
	int blending_src_function;							// ... :D
	int blending_dst_function;							// ... :D
	int blending_logic;									// &,|,~...
	
	int scissor_enabled;								// 1|0
	UX_INTBOX scissor_box;								// {x,y,w,h}
} UX_RENDER;

/* Viewport abstraction: */
typedef struct UX_VIEWPORT {
	unsigned int sync;
	unsigned int width, height;
	unsigned int x,y;
	unsigned int _near, _far;
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

extern int uxgraphics_inited;		//!< graphics system initialized.
extern int uxgraphics_in3D;			//!< last render was 3D.

extern void *framebuffers[2];		//!< framebuffers.	(2? we need a define, cause NDS has 2 displays * 2 buffers = 4 framebuffers perhaps)
extern int fb;						//!< current framebuffer

extern UX_IMAGE		dispBuffer;		//!< Display buffer abstraction to image.
extern UX_IMAGE		drawBuffer;		//!< Draw buffer abstraction to image.
extern UX_RENDER	dRender;		//!< Current active render.
extern UX_VIEWPORT	dView;			//!< Current active viewport.


/*************************
 * Functions             *
 *************************/
extern int uxgraphics_init();		//!< Initialize graphics subsystem
extern void uxgraphics_shutdown();	//!< Deinitialize graphics subsytem

extern void uxgraphics_setViewMode(UX_VIEWPORT view, int force2D, int force3D);
extern void uxgraphics_setViewport(UX_VIEWPORT view, int mode);
extern void uxgraphics_viewmatrix(UX_VIEWPORT view, int mode);
extern void uxgraphics_modelmatrix();

extern void uxgraphics_setRenderMode(UX_RENDER render);

extern void uxgraphics_clearscreen();
extern void uxgraphics_flipscreen();

extern void uxgraphics_renderListMalloc(int size);

#endif