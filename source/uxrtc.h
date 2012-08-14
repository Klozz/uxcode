/*
 * uxrtc.h
 * This file is used to manage clock in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#ifndef UXRTC_H
#define UXRTC_H


#define UXTIME time_t
#define UXTIMERTC u64

extern int uxrtc_inited;

extern int uxrtc_init();
extern void uxrtc_shutdown();

extern int uxrtc_fps();

#endif
