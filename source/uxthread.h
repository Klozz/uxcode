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

/* thread types */
#ifdef WII
	typedef void *(*UXTHREAD_FUNCT)(void *argp);
	typedef lwp_t UXTHREAD_T;
#elif defined(PSP)
	typedef int (*UXTHREAD_FUNCT)(SceSize args, void *argp);
	typedef SceUID UXTHREAD_T;
#else
	typedef void *(*UXTHREAD_FUNCT)(void *argp);
	typedef unsigned int UXTHREAD_T;
#endif


/* Functions exported by threads module */
extern void uxthreads_init();								//!< Init threads system (if required)
extern void uxthreads_shutdown();							//!< Deinit threads system (if required)

extern UXTHREAD_T *uxthread_create(UXTHREAD_FUNCT function, void * arguments, void * stack_addr, unsigned int stack_size, unsigned char priority);

#endif