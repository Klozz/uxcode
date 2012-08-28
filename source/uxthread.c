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

uxthread_t * threads[UXTHREAD_MAXTHREADS];

static unsigned int uxthread_findentry() {
	register int i=0;
	for (;i<UXTHREAD_MAXTHREADS;i++) {
		if (threads[i]==NULL) return i;
	}
	return UXTHREAD_MAXTHREADS+1;
}

UXTHREAD_ENTRY_RESULT uxthread_entry(UXTHREAD_ENTRY_PARAMS) {
	
	/* prepare thread */
	uxthread_t * thread = arg;

	/* initiate task or queue it */
	#ifdef UXTHREAD_HAVEMULTITASK
		int status = 0;
		for (;;){
			if (thread->status == UXTHREAD_READY || thread->status == UXTHREAD_RUNNING) {
				status = thread->function(thread->args, thread->argp);
				if (status == 0) { thread->status = UXTHREAD_CLOSED; }
			}
			if (thread->status == UXTHREAD_CLOSED) { 
				return UXTHREAD_ENTRY_EXITVL;
			}
		}
	#else
		return UXTHREAD_ENTRY_EXITVL;
	#endif
}

/** @defgroup ux_thread Threads

	Thread manager.
	@{
*/

/** 
	\brief Initialize the threads subsystem if needed.
*/
void uxthread_init() {
	register int i=0;
	for (;i<UXTHREAD_MAXTHREADS;i++) { threads[i] = NULL; }
}

/** 
	\brief Terminate the threads subsystem if needed.
*/
void uxthread_shutdown() {
	register int i=0;
	for (;i<UXTHREAD_MAXTHREADS;i++) {
		if (threads[i] != NULL) {
			uxthread_delete(threads[i]);
			threads[i] = NULL;
		}
	}
}

/** 
	\brief If a platform doesn't have multitasking, this function
	performs a step in the internal scheduler.
*/
void uxthread_dostep() {
	register int i=0;
	for (i=0;i<UXTHREAD_MAXTHREADS;i++) {
		if (threads[i] != NULL) {
			if (threads[i]->status == UXTHREAD_READY || threads[i]->status == UXTHREAD_RUNNING) {
				threads[i]->function((threads[i])->args,(threads[i])->argp);
			}
		}
	}
}

/** 
	\brief Create and start (or enqueue) a new thread.
	\param function Entry function to the thread.
	\param arguments Pointer to arguments.
	\param arguments_size Size of data to pass.
	\param stack_addr Base address of stack.
	\param stack_size Size of stack in bytes.
	\param priority Thread priority (0-127)
*/
uxthread_t *uxthread_create(UXTHREAD_FUNCTION function, void * arguments, unsigned int arguments_size, void * stack_addr, unsigned int stack_size, unsigned char priority) {
	
	/* thread allocating and initialization */
	uxthread_t * thread;
	thread = (uxthread_t *)uxmemalloc(sizeof(uxthread_t));
	uxmemset(thread,0,sizeof(uxthread_t));

	thread->function = function;
	thread->argp = arguments;
	thread->args = arguments_size;
	thread->priority = (priority > 127 ? 127 : ( priority < 0 ? 0 : priority));
	thread->status = UXTHREAD_READY;
	thread->number = uxthread_findentry();

	if (thread->number > UXTHREAD_MAXTHREADS) { thread->status = UXTHREAD_CANT_START; }

	#if defined(WII)
		thread->id = LWP_THREAD_NULL;
		int status = LWP_CreateThread( &(thread->id), &uxthread_entry, thread, stack_addr, stack_size, thread->priority);
		if (status == 0) { 
			threads[thread->number] = thread;
			return thread;
		}
	#elif defined(PSP)
		char threadname[15];
		uxmemset(threadname,0,15);
		sprintf(threadname, "thread%08d", thread->number);
		thread->id = sceKernelCreateThread((const char *)threadname, &uxthread_entry, thread->priority, stack_size, PSP_THREAD_ATTR_VFPU, NULL);
		if (not ((unsigned int)(thread->id) & 0x80000000)) { 
			threads[thread->number] = thread;
			sceKernelStartThread(thread->id,sizeof(uxthread_t),(void *)thread);
			return thread;
		}
	#else
		if (thread->status != UXTHREAD_CANT_START) {
			threads[thread->number] = thread;
			return thread;
		}
	#endif

	uxmemfree(thread);
	return NULL;
}

/** 
	\brief Stop and delete a thread.
	\param thread Thread to stop and delete
*/
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

	threads[thread->number] = NULL;
	uxmemfree(thread);
	
	return true;
}

/** @} */