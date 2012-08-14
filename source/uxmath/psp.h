/*
 * uxmath/psp.h
 * This file is used to manage math operations for PlayStationPortable in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#if defined(PSP)
#include <pspmath.h>
#include <fastmath.h>

extern float uxadd(float a, float b);                           // a + b
extern float uxsub(float a, float b);                           // a - b
extern float uxmul(float a, float b);                           // a * b
extern float uxdiv(float a, float b);                           // a / b
extern int uxidiv(int a, int b);                                // int( a / b )
extern float uxabsf(float x);                                   // |x|
#define uxmodf modf
extern float uxceilf(float x);                                  // ceil(x)
extern float uxfloorf(float x);                                 // floor(x)
extern float uxfmodf(float x, float y);                         // x % y
#define uxpowf(a,b) vfpu_powf(a,b)                              // x^y
extern float uxsqrtf(float x);                                  // sqrt(x)
#define uxlogf(x) vfpu_logf(x)                                  // log(x)
extern float uxlog2f(float x);                                  // log2(x)
extern float uxlog10f(float x);                                 // log10(x)
extern float uxhipotenuse(float x, float y);                    // sqrt( x^2 + y^2 )
extern float uxclampf(float x, float min, float max);           // ( a > max ? max : ( a < min ? min : a ) )
extern float uxmaxf(float x, float y);                          // max(a,b)
extern float uxminf(float x, float y);                          // min(a,b)
extern float uxrsq(float x);                                    // 1 / sqrt(x)
extern int uxf2i(float x);                                      // (int)(x)
extern float uxi2f(int x);                                      // (float)(x)
#define uxsinf(x) vfpu_sinf(x)                                  // sin(x)
#define uxcosf(x) vfpu_cosf(x)                                  // cos(x)
#define uxtanf(x) vfpu_tanf(x)                                  // tan(x)
#define uxasinf(x) vfpu_asinf(x)                                // asin(x)
#define uxacosf(x) vfpu_acosf(x)                                // acos(x)
#define uxatanf(x) vfpu_atanf(x)                                // atan(x)
#define uxatan2f(x,y) vfpu_atan2f(x,y)                          // atan2(y,x)
#define uxsinhf(x) vfpu_sinhf(x)                                // sinh(x)
#define uxcoshf(x) vfpu_coshf(x)                                // cosh(x)
#define uxtanhf(x) vfpu_tanhf(x)                                // tanh(x)
#define uxsincosf(x,s,c) vfpu_sincos(x,s,c)                     // sincos(x,s,c)
#define uxexpf(x) vfpu_expf(x)                                  // expf(x)
#define uxsrand vfpu_srand
#define uxrandf vfpu_randf
#define uxfrexpf frexpf
#define uxldexpf ldexpf

/*
vfpu_ease_in_out
vfpu_normalize_vector
vfpu_zero_vector
vfpu_scale_vector
vfpu_add_vector
...
*/
#endif