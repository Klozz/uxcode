/*
 * uxmem.c
 * This file is used to manage memory in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#include "utils.h"

void *uxmemalloc(UXFILESIZE_T size) {
#ifdef PSP	
	return memalign(16,size);
#else
	return malloc(size);
#endif
}

void *uxmemcopy(void *s1, const void *s2, UXFILESIZE_T n) {
	return memcpy(s1,s2,n);
}

#if defined(_WIN32)
	#define uxmemalign(x,y) uxmemalloc(y)
#else
void *memalign(UXFILESIZE_T blocksize, UXFILESIZE_T size);
void *uxmemalign(UXFILESIZE_T blocksize, UXFILESIZE_T size) {
	return memalign(blocksize,size);
}
#endif

void *uxmembyteswap(int* s, int size) { 
	int i, a; 
	for(i=0;i<size;i++) {
		a = s[i]; s[i] = intswap(a);
	}
	return s;
}


void *uxmemset(void *s, int c, UXFILESIZE_T n) {
	return memset(s,c,n);
}

void uxmemfree(void *handle) {
	free(handle);
}

void *uxstrdup(void *string) {
	UXFILESIZE_T l = strlen(string)+1;
	void *ptr = (void *)uxmemalloc(l);
	uxmemset(ptr,0,l);
	uxmemcopy(ptr,string,l-1);
	return ptr;
}


