#if defined(PSP)
	typedef unsigned int UXCOLOR;
	typedef u32 UX_COLORU32;
	typedef ScePspFMatrix4 UX_MATRIX;
	typedef ScePspFMatrix4 UX_MATRIX4;

	#define UXRGBA(r,g,b,a) ((r) | ((g)<<8) | ((b)<<16) | ((a)<<24))
	#define UXR(x) ((x & 0xFF000000) >> 24)
	#define UXG(x) ((x & 0x00FF0000) >> 16)
	#define UXB(x) ((x & 0x0000FF00) >>  8)
	#define UXA(x) (x & 0x000000FF)
	
	#define u32UXRGBA(r,g,b,a) ((r) | ((g)<<8) | ((b)<<16) | ((a)<<24))
	#define u32UXR(x) ((x & 0xFF000000) >> 24)
	#define u32UXG(x) ((x & 0x00FF0000) >> 16)
	#define u32UXB(x) ((x & 0x0000FF00) >> 8)
	#define u32UXA(x) (x & 0x000000FF)
	
	/* Constantes UX_MOLONAS */
	typedef enum {
		UX_GL_NEVER    = 0,
		UX_GL_ALWAYS   = 1,
		UX_GL_EQUAL    = 2,
		UX_GL_NOTEQUAL = 3,
		UX_GL_LESS     = 4,
		UX_GL_LEQUAL   = 5,
		UX_GL_GREATER  = 6,
		UX_GL_GEQUAL   = 7
	} UX_BLENDMODE;
	
	typedef enum {
		UX_GL_CULLBACK  = GU_CW,
		UX_GL_CULLFRONT = GU_CCW
	} UX_CULLFACING;
	
	typedef enum {
		UX_BO_ADD         = GU_ADD,
		UX_BO_SUBTRACT    = GU_SUBTRACT,
		UX_BO_INVSUBTRACT = GU_REVERSE_SUBTRACT,
		UX_BO_MIN         = GU_MIN,
		UX_BO_MAX         = GU_MAX,
		UX_BO_ABS         = GU_ABS,
		UX_BO_BIT         = 10
	} UX_BLENDOPERATOR;
	
	typedef enum {
		UX_BF_SRC_COLOR = GU_SRC_COLOR,
		UX_BF_ONE_MINUS_SRC_COLOR = GU_ONE_MINUS_SRC_COLOR,
		UX_BF_SRC_ALPHA = GU_SRC_ALPHA,
		UX_BF_ONE_MINUS_SRC_ALPHA = GU_ONE_MINUS_SRC_ALPHA,
		UX_BF_DST_ALPHA = GU_DST_ALPHA,
		UX_BF_ONE_MINUS_DST_ALPHA = GU_ONE_MINUS_DST_ALPHA,
		UX_BF_DST_COLOR = GU_DST_COLOR,
		UX_BF_ONE_MINUS_DST_COLOR = GU_ONE_MINUS_DST_COLOR,
		UX_BF_ONE = -1,
		UX_BF_ZERO = -1,
		UX_BF_FIX = GU_FIX
	} UX_BLENDFUNCTION;
	
	typedef enum {
		UX_BL_AND = GU_AND,
		UX_BL_CLEAR = GU_CLEAR,
		UX_BL_COPY = GU_COPY,
		UX_BL_EQUIV = GU_EQUIV,
		UX_BL_INV = GU_INVERTED,
		UX_BL_INVAND = GU_AND_INVERTED,
		UX_BL_INVCOPY = GU_COPY_INVERTED,
		UX_BL_INVOR = GU_OR_INVERTED,
		UX_BL_NAND = GU_NAND,
		UX_BL_NOOP = GU_NOOP,
		UX_BL_NOR	= GU_NOR,
		UX_BL_OR = GU_OR,
		UX_BL_REVAND = GU_AND_REVERSE,
		UX_BL_REVOR = GU_OR_REVERSE,
		UX_BL_SET = GU_SET,
		UX_BL_XOR = GU_XOR
	} UX_BLENDLOGIC;
	
	typedef enum {
		UX_AT_NEVER = GU_NEVER,
		UX_AT_ALWAYS = GU_ALWAYS,
		UX_AT_EQUAL = GU_EQUAL,
		UX_AT_NEQUAL = GU_NOTEQUAL,
		UX_AT_LESS = GU_LESS,
		UX_AT_LEQUAL = GU_LEQUAL,
		UX_AT_GREATER = GU_GREATER,
		UX_AT_GEQUAL = GU_GEQUAL
	} UX_ALPHATEST;
#endif