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

uxthread_t * threads[100];


void uxthread_dostep(void) {
	register int i=0;
	for (i=0;i<100;i++) {
		if (threads[i] != NULL) {
			if (threads[i]->status == UXTHREAD_READY || threads[i]->status == UXTHREAD_RUNNING)
				(threads[i])->function((threads[i])->args,(threads[i])->argp);
			continue;
		}
		return;
	}
}

UXTHREAD_ENTRY_RESULT uxthread_entry(UXTHREAD_ENTRY_PARAMS) {
	uxthread_t * thread = arg;
	int status = 0;

	thread->status = UXTHREAD_READY;
	if (UXTHREAD_HAVEMULTITASK) {
		for (;;){
			status = thread->function(thread->args, thread->argp);
			if (status == 0) { thread->status = UXTHREAD_CLOSED; }
			if (thread->status == UXTHREAD_CLOSED) { return UXTHREAD_ENTRY_EXITVL; }
		}
	} else {
		threads[uxthread_number++] = thread;
		return UXTHREAD_ENTRY_EXITVL;
	}
}



uxthread_t *uxthread_create(UXTHREAD_FUNCTION function, void * arguments, unsigned int arguments_size, void * stack_addr, unsigned int stack_size, unsigned char priority) {
	
	/* thread allocating and initialization */
	uxthread_t * thread;
	thread = (uxthread_t *)uxmemalloc(sizeof(uxthread_t));
	uxmemset(thread,0,sizeof(uxthread_t));

	thread->status = UXTHREAD_INITING;
	thread->function = function;
	thread->argp = arguments;
	thread->args = arguments_size;
	thread->argx = (void *)uxmemalloc(sizeof(int)*100);
	thread->argz = sizeof(int)*100;
	thread->priority = priority;

	#if defined(WII)
		thread->id = LWP_THREAD_NULL;
		int status = LWP_CreateThread( &(thread->id), &uxthread_entry, thread, stack_addr, stack_size, priority);
		if (status == 0) { return thread; }
	#endif

	#if defined(PSP)
		char threadname[15];
		uxmemset(threadname,0,15);
		sprintf(threadname, "thread%08d", uxthread_number);

		thread->id = sceKernelCreateThread((const char *)threadname, &uxthread_entry, priority, stack_size, PSP_THREAD_ATTR_VFPU, NULL);
		if (not ((unsigned int)(thread->id) & 0x80000000)) { 
			sceKernelStartThread(thread->id,sizeof(uxthread_t),(void *)thread);
			return thread;
		}
	#endif

	uxmemfree(thread->argx);
	uxmemfree(thread);
	return NULL;
}

unsigned int uxthread_delete(uxthread_t *thread) {
	if (thread == NULL) { return false; }

	#if defined(WII)
		thread->status = UXTHREAD_CLOSED;
		LWP_ResumeThread(thread->id);
		LWP_SuspendThread(thread->id);
	#elif defined(PSP)
		sceKernelTerminateThread( thread->id );
		sceKernelDeleteThread( thread->id );
	#endif

	uxmemfree(thread->argx);
	uxmemfree(thread);
	
	return true;
}


void uxthread_init() {
	register int i=0;
	for (i=0;i<100;i++) { threads[i] = NULL; }
}

void uxthread_shutdown() {
	/** close threads[i]; */	
}