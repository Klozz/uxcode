#ifndef UXMEMORY_H
#define UXMEMORY_H


// Platform dependent defines:
#include "uxmem/nds.h"
#include "uxmem/wii.h"
#include "uxmem/psp.h"
#include "uxmem/win.h"


// VRAM Manager	[platform dependant]
extern void uxmemory_init();



// RAM Manager









#if defined(_WIN32)
	#define uxmemalign(x,y) uxmemalloc(y)
#else
extern void *uxmemalign(UXFILESIZE_T blocksize, UXFILESIZE_T size);
#endif

extern void *uxmemalloc(unsigned int size);
extern void *uxmemset(void *s, int c, UXFILESIZE_T n);
extern void *uxmemcopy(void *s1, const void *s2, UXFILESIZE_T n);
extern void uxmemfree(void *handle);

void *uxmembyteswap(int* s, int size);
extern void *uxstrdup(void *string);


#endif