/*
 * uxcontrols/wii.h
 * This file is used to manage graphics subsystem for Wii in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#if defined(WII)
	typedef GXColor UXCOLOR;
	typedef u32 UX_COLORU32;
	typedef Mtx 	UX_MATRIX;
	typedef Mtx44	UX_MATRIX4;
	
	#define UXRGBA(r,g,b,a) (UXCOLOR){ r,g,b,a }
	#define UXR(x) x.r
	#define UXG(x) x.g
	#define UXB(x) x.b
	#define UXA(x) x.a

	#define u32UXR(c)  (((c) >>24) &0xFF)  /**< Extract red component of colour. */
	#define u32UXG(c)  (((c) >>16) &0xFF)  /**< Extract green component of colour. */
	#define u32UXB(c)  (((c) >> 8) &0xFF)  /**< Extract blue component of colour. */
	#define u32UXA(c)  ( (c)       &0xFF)  /**< Extract alpha component of colour. */
	
	#define u32UXRGBA(r,g,b,a) ( (u32)( ( ((u32)(r))<<24) | ((((u32)(g)) &0xFF) <<16) | ((((u32)(b)) &0xFF) << 8) | ( ((u32)(a)) &0xFF) ) )

	#define UXCOLOR2U32COLOR(x) u32UXRGBA(x.r,x.g,x.b,x.a)
	
	/* Constantes UX_MOLONAS */
	typedef enum {
		UX_GL_NEVER=0,
		UX_GL_ALWAYS=7,
		UX_GL_EQUAL=2,
		UX_GL_NOTEQUAL=5,
		UX_GL_LESS=1,
		UX_GL_LEQUAL=3,
		UX_GL_GREATER=4,
		UX_GL_GEQUAL=6
	} UX_BLENDMODE;
	
	typedef enum {
		UX_GL_CULLBACK = GX_CULL_BACK,
		UX_GL_CULLFRONT = GX_CULL_FRONT
	} UX_CULLFACING;
	
    typedef enum {
		UX_BO_ADD = GX_BM_BLEND,
		UX_BO_SUBTRACT = GX_BM_SUBTRACT,
		UX_BO_INVSUBTRACT = -1,
		UX_BO_MIN = -1,
		UX_BO_MAX = -1,
		UX_BO_ABS = -1,
		UX_BO_BIT = GX_BM_LOGIC
	} UX_BLENDOPERATOR;
	
	typedef enum {
		UX_BF_SRC_COLOR = GX_BL_SRCCLR,
		UX_BF_ONE_MINUS_SRC_COLOR = GX_BL_INVSRCCLR,
		UX_BF_SRC_ALPHA = GX_BL_SRCALPHA,
		UX_BF_ONE_MINUS_SRC_ALPHA = GX_BL_INVSRCALPHA,
		UX_BF_DST_ALPHA = GX_BL_DSTALPHA,
		UX_BF_ONE_MINUS_DST_ALPHA = GX_BL_INVDSTALPHA,
		UX_BF_DST_COLOR = GX_BL_DSTCLR,
		UX_BF_ONE_MINUS_DST_COLOR = GX_BL_INVDSTCLR,
		UX_BF_ONE = GX_BL_ONE,
		UX_BF_ZERO = GX_BL_ZERO,
		UX_BF_FIX = -1,
	} UX_BLENDFUNCTION;
	
	typedef enum {
		UX_BL_AND = GX_LO_AND,
		UX_BL_CLEAR = GX_LO_CLEAR,
		UX_BL_COPY = GX_LO_COPY,
		UX_BL_EQUIV = GX_LO_EQUIV,
		UX_BL_INV = GX_LO_INV,
		UX_BL_INVAND = GX_LO_INVAND,
		UX_BL_INVCOPY = GX_LO_INVCOPY,
		UX_BL_INVOR = GX_LO_INVOR,
		UX_BL_NAND = GX_LO_NAND,
		UX_BL_NOOP = GX_LO_NOOP,
		UX_BL_NOR = GX_LO_NOR,
		UX_BL_OR = GX_LO_OR,
		UX_BL_REVAND = GX_LO_REVAND,
		UX_BL_REVOR = GX_LO_REVOR,
		UX_BL_SET = GX_LO_SET,
		UX_BL_XOR = GX_LO_XOR
	} UX_BLENDLOGIC;
	typedef enum {
		UX_AT_NEVER = GX_NEVER,
		UX_AT_ALWAYS = GX_ALWAYS,
		UX_AT_EQUAL = GX_EQUAL,
		UX_AT_NEQUAL = GX_NEQUAL,
		UX_AT_LESS = GX_LESS,
		UX_AT_LEQUAL = GX_LEQUAL,
		UX_AT_GREATER = GX_GREATER,
		UX_AT_GEQUAL = GX_GEQUAL
	} UX_ALPHATEST;
	
	//platform dependant variables:
	
	extern GXRModeObj *rmode;
	extern void *gp_fifo;
#endif