/*
 * uxthread.c
 * This file is used to manage threads subsystem in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#include "utils.h"

unsigned int uxthread_number = 0;

UXTHREAD_T *uxthread_create(UXTHREAD_FUNCT function, void * arguments, void * stack_addr, unsigned int stack_size, unsigned char priority) {

	UXTHREAD_T * thread;
	thread = (UXTHREAD_T *)uxmemalloc(sizeof(UXTHREAD_T));

	#if defined(WII)

		int status = LWP_CreateThread(thread,function,arguments,stack_addr,stack_size,priority);
		if (status == 0) { return thread; }

	#elif defined(PSP)

		char threadname[10];
		uxmemset(threadname,0,10);
		sprintf(threadname, "thread%08d", uxthread_number++);
		*thread = sceKernelCreateThread((const char *)threadname, function, priority, stack_size, PSP_THREAD_ATTR_VFPU, NULL);
		if (not ((unsigned int)(*thread) & 0x80000000)) { return thread; }

	#endif

	return NULL;
}



void uxthread_init() {
	/* init thread subsystem */
}

void uxthread_shutdown() {
	/* shutdown thread subsystem */
}