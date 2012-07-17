#ifndef UXRTC_H
#define UXRTC_H


#define UXTIME time_t
#define UXTIMERTC u64

extern int uxrtc_inited;

extern int uxrtc_init();
extern void uxrtc_shutdown();

extern int uxrtc_fps();

#endif
