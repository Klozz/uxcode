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