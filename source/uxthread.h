/*
 * uxthread.h
 * This file is used to manage threads subsystem in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#ifndef UXTHREAD_H
#define UXTHREAD_H

#define UXTHREAD_MAXTHREADS 100

/* Entry function helpers */
#ifdef WII
	#define UXTHREAD_ENTRY_RESULT void *
	#define UXTHREAD_ENTRY_EXITVL NULL
	#define UXTHREAD_ENTRY_PARAMS void *arg
	#define UXTHREAD_HAVEMULTITASK true
#elif defined(PSP)
	#define UXTHREAD_ENTRY_RESULT int
	#define UXTHREAD_ENTRY_EXITVL 0
	#define UXTHREAD_ENTRY_PARAMS SceSize args, void *arg
	#define UXTHREAD_HAVEMULTITASK true
#else
	#define UXTHREAD_ENTRY_RESULT int
	#define UXTHREAD_ENTRY_EXITVL 0
	#define UXTHREAD_ENTRY_PARAMS unsigned int args, void *arg
	#undef UXTHREAD_HAVEMULTITASK
#endif


enum UXTHREAD_STATUS { 
	UXTHREAD_READY,
	UXTHREAD_CLOSED,
	UXTHREAD_SUSPENDED,
	UXTHREAD_ALREADY_SUSPENDED,
	UXTHREAD_RUNNING,
	UXTHREAD_CANT_START
};

#if defined(WII)
	typedef void *(*UXTHREAD_EF)(void *argp);
	typedef lwp_t UXTHREAD_T;
#elif defined(PSP)
	typedef int (*UXTHREAD_EF)(SceSize args, void *argp);
	typedef SceUID UXTHREAD_T;
#else
	typedef int (*UXTHREAD_EF)(unsigned int args, void *argp);
	typedef unsigned int UXTHREAD_T;
#endif

typedef int (*UXTHREAD_FUNCTION)(unsigned int argsize, void *argpointer);	//!< Thread function type.

typedef struct uxthread_t {
	enum UXTHREAD_STATUS status;			//!< Thread status.
	UXTHREAD_FUNCTION function;				//!< Entry / thread function.
	void * argp;							//!< Input argument pointer.
	unsigned int args;						//!< Input argument size.
	unsigned char priority;					//!< Priority : 0-127
	UXTHREAD_T id;							//!< Internal ID.
	unsigned int number;					//!< Internal scheduler number.
} uxthread_t;

/* Functions exported by threads module */
extern void uxthreads_init();								//!< Init threads system (if required)
extern void uxthreads_shutdown();							//!< Deinit threads system (if required)

extern uxthread_t *uxthread_create(UXTHREAD_FUNCTION function, void * arguments, unsigned int arguments_size, void * stack_addr, unsigned int stack_size, unsigned char priority);
extern unsigned int uxthread_delete(uxthread_t *thread);

#endif