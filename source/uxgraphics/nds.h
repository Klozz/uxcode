#if defined(NDS)
	typedef unsigned short UXCOLOR;
	typedef u16 UX_COLORU32;
	typedef m3x3 UX_MATRIX;
	typedef m4x4 UX_MATRIX4;
	
	#define UXRGBA(r,g,b,a) ((r) | ((g)<<4) | ((b)<<8) | ((a)<<12))
	#define UXR(x) ((x & 0xF000) >> 12)
	#define UXG(x) ((x & 0x0F00) >>  8)
	#define UXB(x) ((x & 0x00F0) >>  4)
	#define UXA(x)  (x & 0x000F)
	
	#define u32UXRGBA(r,g,b,a) ((r) | ((g)<<4) | ((b)<<8) | ((a)<<12))
	#define u32UXR(x) ((x & 0xF000) >> 12)
	#define u32UXG(x) ((x & 0x0F00) >>  8)
	#define u32UXB(x) ((x & 0x00F0) >>  4)
	#define u32UXA(x)  (x & 0x000F)
	
	/* Constantes UX_MOLONAS */
	typedef enum {
		UX_GL_NEVER = -1,
		UX_GL_ALWAYS=-1,
		UX_GL_EQUAL=-1,
		UX_GL_NOTEQUAL=-1,
		UX_GL_LESS=-1,
		UX_GL_LEQUAL=-1,
		UX_GL_GREATER=-1,
		UX_GL_GEQUAL=-1	
	} UX_BLENDMODE;
	
	typedef enum {
		UX_GL_CULLBACK = -1,
		UX_GL_CULLFRONT = -1
	} UX_CULLFACING;
	
    typedef enum {
		UX_BO_ADD = -1,
		UX_BO_SUBTRACT = -1,
		UX_BO_INVSUBTRACT = -1,
		UX_BO_MIN = -1,
		UX_BO_MAX = -1,
		UX_BO_ABS = -1,
		UX_BO_BIT = -1
	} UX_BLENDOPERATOR;
	
	typedef enum {
		UX_BF_SRC_COLOR = -1,
		UX_BF_ONE_MINUS_SRC_COLOR = -1,
		UX_BF_SRC_ALPHA = -1,
		UX_BF_ONE_MINUS_SRC_ALPHA = -1,
		UX_BF_DST_ALPHA = -1,
		UX_BF_ONE_MINUS_DST_ALPHA = -1,
		UX_BF_DST_COLOR = -1,
		UX_BF_ONE_MINUS_DST_COLOR = -1,
		UX_BF_ONE = -1,
		UX_BF_ZERO = -1,
		UX_BF_FIX = -1,
	} UX_BLENDFUNCTION;
	
	typedef enum {
		UX_BL_AND = -1,
		UX_BL_CLEAR = -1,
		UX_BL_COPY = -1,
		UX_BL_EQUIV = -1,
		UX_BL_INV = -1,
		UX_BL_INVAND = -1,
		UX_BL_INVCOPY = -1,
		UX_BL_INVOR = -1,
		UX_BL_NAND = -1,
		UX_BL_NOOP = -1,
		UX_BL_NOR = -1,
		UX_BL_OR = -1,
		UX_BL_REVAND = -1,
		UX_BL_REVOR = -1,
		UX_BL_SET = -1,
		UX_BL_XOR = -1
	} UX_BLENDLOGIC;
	
	typedef enum {
		UX_AT_NEVER = -1,
		UX_AT_ALWAYS = -1,
		UX_AT_EQUAL = -1,
		UX_AT_NEQUAL = -1,
		UX_AT_LESS = -1,
		UX_AT_LEQUAL = -1,
		UX_AT_GREATER = -1,
		UX_AT_GEQUAL = -1
	} UX_ALPHATEST;
#endif