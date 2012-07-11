#if defined(NDS)
#include <math.h>


#define uxadd(a,b) (a+b)
#define uxsub(a,b) (a-b)
#define uxmul(a,b) (a*b)
#define uxdiv(a,b) (a/b)
#define uxidiv(a,b) (int)((int)a/(int)b)
#define uxabsf fabsf
#define uxmodf modf
#define uxceilf ceilf
#define uxfloorf floorf
#define uxfmodf fmodf
#define uxpowf powf
#define uxsqrtf sqrtf
#define uxlogf logf
#define uxlog2f(x) (logf(x)/logf(2))
#define uxlog10f log10f
#define uxhipotenuse(x,y) sqrtf( powf(x,2) + powf(y,2) )
#define uxsincosf(x,s,c) *s = sinf( x ); *c = cosf( x )
#define uxclampf(val, min, max) ((val)>(max)?(max):((val)<(min)?(min):(val)))
#define uxminf(x, y) (((x) < (y)) ? (x) : (y))
#define uxmaxf(x, y) (((x) > (y)) ? (x) : (y))
#define uxrsq(x) (1.0f / sqrtf(x))
#define uxf2i(x) (int)(x)
#define uxi2f(x) (float)(x)
#define uxsinf sinf
#define uxcosf cosf
#define uxtanf tanf
#define uxasinf asinf
#define uxacosf acosf
#define uxatanf atanf
#define uxatan2f atan2f
#define uxsinhf sinhf
#define uxcoshf coshf
#define uxtanhf tanhf
#define uxexpf expf
#define uxsrand srand
#define uxrandf(a,b) ( ( (float)rand() / (float)RAND_MAX ) * (((float)(b)-(float)(a)) + (float)(a)))
#define uxfrexpf frexpf
#define uxldexpf ldexpf
#endif