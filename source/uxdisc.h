/*
 * uxdisc.h
 * This file is used to manage discs and other removable media in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#ifndef UXDISC_H
#define UXDISC_H


/* Functions exported by uxdisc module */
extern void uxdisc_init();								//!< Init disc system (if required)
extern void uxdisc_shutdown();							//!< Deinit disc system (if required)

extern int uxdisc_waitfordisc();
extern int uxdisc_check();								//!< Disc / medium present.
extern int uxdisc_mount();								//!< Mount disc / medium.


extern int uxdisc_inited;
extern int uxdisc_mounted;

#endif