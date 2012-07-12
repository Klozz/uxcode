/* UXCODE MATH IMPLEMENTATION */

/** @defgroup ux_math Math functions.

	Math functions.
	@{
		\todo
			- math documentation
	@} */
	
#ifdef PSP
float uxadd(float a, float b){
   float result;
   __asm__ volatile (
           "mtv %1, S000\n"
           "mtv %2, S001\n"
           "vadd.s S002, S000, S001\n"
           "mfv %0, S002\n"
           : "=r"(result) 
           : "r"(a), "r"(b)
   );
   return result;
}

float uxsub(float a, float b){               // a - b
   float result;
   __asm__ volatile (
       "mtv    %1, S000\n"
       "mtv    %2, S001\n"
       "vsub.s S002, S000, S001\n"
       "mfv    %0, S002\n"
       : "=r"(result) : "r"(a), "r"(b));
   return result;
}

float uxmul(float a, float b){              // a * b
   float result;
   __asm__ volatile (
       "mtv    %1, S000\n"
       "mtv    %2, S001\n"
       "vmul.s S002, S000, S001\n"
       "mfv    %0, S002\n"
       : "=r"(result) : "r"(a), "r"(b));
   return result;
}

float uxdiv(float a, float b) {              // a * (1/b)
   float result;
   __asm__ volatile (
       "mtv    %1, S000\n"
       "mtv    %2, S001\n"
       "vrcp.s  S001, S001\n"
       "vmul.s  S000, S000, S001\n"             
       "mfv    %0, S000\n"
       : "=r"(result) : "r"(a), "r"(b));
   return result;
}

int uxidiv(int a, int b) {
	int result;
	__asm__ volatile (
        "mtv    %1, S000\n"
        "mtv    %2, S001\n"
		"vi2f.s	  S002, S000, 0\n"
		"vi2f.s	  S003, S001, 0\n"
		"vrcp.s  S003, S003\n"
		"vmul.s  S000, S002, S003\n"
		"vf2id.s  S001, S000, 0\n"
		"mfv      %0, S001\n"
       : "=r"(result) : "r"(a), "r"(b));
	return result;
}

float uxabsf(float x) {
	float result;
	__asm__ volatile (
		"mtv      %1, S000\n"
		"vabs.s   S000, S000\n"
		"mfv      %0, S000\n"
	: "=r"(result) : "r"(x));
	return result;
}

float uxceilf(float x) {
	float result;
	__asm__ volatile (
		"mtv      %1, S000\n"
		"vf2iu.s  S000, S000, 0\n"
		"vi2f.s	  S000, S000, 0\n"
		"mfv      %0, S000\n"
	: "=r"(result) : "r"(x));
	return result;
}
float uxfloorf(float x) {
	float result;
	__asm__ volatile (
		"mtv      %1, S000\n"
		"vf2id.s  S000, S000, 0\n"
		"vi2f.s	  S000, S000, 0\n"
		"mfv      %0, S000\n"
	: "=r"(result) : "r"(x));
	return result;
}

float uxsqrtf(float x) {
	float result;
	__asm__ volatile (
		"mtv     %1, S000\n"
		"vsqrt.s S000, S000\n"
		"mfv     %0, S000\n"
	: "=r"(result) : "r"(x));
	return result;
}

float uxfmodf(float x, float y) {
	float result; // return x-y*((int)(x/y));
	__asm__ volatile (
		"mtv       %2, S001\n"
		"mtv       %1, S000\n"
		"vrcp.s    S002, S001\n"
		"vmul.s    S003, S000, S002\n"
		"vf2iz.s   S002, S003, 0\n"
		"vi2f.s    S003, S002, 0\n"
		"vmul.s    S003, S003, S001\n"
		"vsub.s    S000, S000, S003\n"
		"mfv       %0, S000\n"
	: "=r"(result) : "r"(x), "r"(y));
	return result;
}

float uxlog2f(float x) {
    float result;
    __asm__ volatile (
        "mtv     %1, S000\n"
        "vlog2.s S000, S000\n"
        "mfv     %0, S000\n"
        : "=r"(result) : "r"(x));
    return result;
}

float uxlog10f(float x)
{
    float result;
    __asm__ volatile (
        "mtv     %1, S000\n"
        "vcst.s  S001, VFPU_LOG2TEN\n"
        "vrcp.s  S001, S001\n"
        "vlog2.s S000, S000\n"
        "vmul.s  S000, S000, S001\n"
        "mfv     %0, S000\n"
        : "=r"(result) : "r"(x));
    return result;
}

float uxhipotenuse(float x, float y) {
	float result;
	__asm__ volatile (
	   "mtv    %1, S000\n"
       "mtv    %2, S001\n"
       "vmul.s S002, S000, S000\n"
	   "vmul.s S003, S001, S001\n"
	   "vadd.s S000, S002, S003\n"
	   "vsqrt.s S000, S000\n"
	   "mfv     %0, S000\n"
       : "=r"(result) : "r"(x), "r"(y));
	return result;
}

float uxclampf(float x, float min, float max) {
	float result;
	__asm__ volatile (
		"mtv      %1, S000\n"
		"mtv      %2, S001\n"
		"mtv      %3, S002\n"
		"vmax.s   S003, S000, S001\n"
		"vmin.s   S001, S003, S002\n"
		"mfv      %0, S001\n"
	: "=r"(result) : "r"(x), "r"(min), "r"(max));
	return result;
}

float uxmaxf(float x, float y) {
	float result;
	__asm__ volatile (
		"mtv      %1, S000\n"
		"mtv      %2, S001\n"
		"vmax.s   S002, S000, S001\n"
		"mfv      %0, S002\n"
	: "=r"(result) : "r"(x), "r"(y));
	return result;
}

float uxminf(float x, float y) {
	float result;
	__asm__ volatile (
		"mtv      %1, S000\n"
		"mtv      %2, S001\n"
		"vmin.s   S002, S000, S001\n"
		"mfv      %0, S002\n"
	: "=r"(result) : "r"(x), "r"(y));
	return result;
}

float uxrsq(float x) {
	float result;
	__asm__ volatile (
		"mtv		%0, S000\n"
		"vrsq.s		S000, S000\n"
		"mfv		%0, S000\n"
	: "=r"(result): "r"(x));
	return result;
}

int uxf2i(float x) {
	int result;
	__asm__ volatile (
		"mtv      %1, S000\n"
		"vf2id.s  S001, S000, 0\n"
		"mfv      %0, S001\n"
	: "=r"(result) : "r"(x));
	return result;
}

float uxi2f(int x) {
	float result;
	__asm__ volatile (
		"mtv      %1, S000\n"
		"vi2f.s	  S001, S000, 0\n"
		"mfv      %0, S001\n"
	: "=r"(result) : "r"(x));
	return result;
}


#endif