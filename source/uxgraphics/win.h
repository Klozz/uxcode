#if defined(_WIN32)
	typedef struct { float r; float g; float b; float a; } UXCOLOR;
	typedef u32 UX_COLORU32;
	typedef int UX_MATRIX;
	typedef int UX_MATRIX4;
	
	enum UX_PIXELFORMAT {
		UX_PF_5650=100,							//!< 
		UX_PF_5551=100,							//!< 
		UX_PF_4444=100,							//!< 
		UX_PF_6666=100,							//!< 
		UX_PF_8880=100,							//!< 
		UX_PF_8888=0,							//!< best-quality option by default
		UX_PF_2BIT=100,							//!<
		UX_PF_4BIT=100,							//!< 
		UX_PF_8BIT=100,							//!< 
		UX_PF_DXT1=100,							//!< 
		UX_PF_DXT3=100,							//!< 
		UX_PF_DXT5=100							//!< 
	};
	
	
	#define UXRGBA(r,g,b,a) (UXCOLOR){ (float)(r / 255.0f), (float)(g / 255.0f), (float)(b / 255.0f), (float)(a / 255.0f) }
	#define UXR(x) x.r
	#define UXG(x) x.g
	#define UXB(x) x.b
	#define UXA(x) x.a
	
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
		UX_GL_CULLBACK  = GL_BACK,
		UX_GL_CULLFRONT = GL_FRONT
	} UX_CULLFACING;
	
	typedef enum {
		UX_BO_ADD         = GL_FUNC_ADD,
		UX_BO_SUBTRACT    = GL_FUNC_SUBTRACT,
		UX_BO_INVSUBTRACT = GL_FUNC_REVERSE_SUBTRACT,
		UX_BO_MIN         = GL_MIN,
		UX_BO_MAX         = GL_MAX,
		UX_BO_ABS         = -1,
		UX_BO_BIT         = GL_LOGIC_OP
	} UX_BLENDOPERATOR;
	
	typedef enum { 
		UX_BF_SRC_COLOR           = GL_SRC_COLOR,
		UX_BF_ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
		UX_BF_SRC_ALPHA           = GL_SRC_ALPHA,
		UX_BF_ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
		UX_BF_DST_ALPHA           = GL_DST_ALPHA,
		UX_BF_ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
		UX_BF_DST_COLOR           = GL_DST_COLOR,
		UX_BF_ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
		UX_BF_ONE                 = GL_ONE,
		UX_BF_ZERO                = GL_ZERO,
		UX_BF_FIX                 = -1
	} UX_BLENDFUNCTION;
	
	typedef enum { 
		UX_BL_AND     = GL_AND,
		UX_BL_CLEAR   = GL_CLEAR,
		UX_BL_COPY    = GL_COPY,
		UX_BL_EQUIV   = GL_EQUIV,
		UX_BL_INV     = GL_INVERT,
		UX_BL_INVAND  = GL_AND_INVERTED,
		UX_BL_INVCOPY = GL_COPY_INVERTED,
		UX_BL_INVOR   = GL_OR_INVERTED,
		UX_BL_NAND    = GL_NAND,
		UX_BL_NOOP    = GL_NOOP,
		UX_BL_NOR     = GL_NOR,
		UX_BL_OR      = GL_OR,
		UX_BL_REVAND  = GL_AND_REVERSE,
		UX_BL_REVOR   = GL_OR_REVERSE,
		UX_BL_SET     = GL_SET,
		UX_BL_XOR     = GL_XOR
	} UX_BLENDLOGIC;

	typedef enum { 
		UX_AT_NEVER   = GL_NEVER,
		UX_AT_ALWAYS  = GL_ALWAYS,
		UX_AT_EQUAL   = GL_EQUAL,
		UX_AT_NEQUAL  = GL_NOTEQUAL,
		UX_AT_LESS    = GL_LESS,
		UX_AT_LEQUAL  = GL_LEQUAL,
		UX_AT_GREATER = GL_GREATER,
		UX_AT_GEQUAL  = GL_GEQUAL
	} UX_ALPHATEST;
	
	//platform dependant variables:
	
	extern HWND handleWnd;
	extern HDC handleDC;
	extern HGLRC handleRC;

#endif