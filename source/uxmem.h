/*
 * uxmem.h
 * This file is used to manage memory in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#ifndef UXMEMORY_H
#define UXMEMORY_H

extern void uxmemory_init();
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