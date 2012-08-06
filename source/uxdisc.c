#include "utils.h"

int uxdisc_inited  = false;
int uxdisc_mounted = false;

int uxdisc_check() {
    #if defined(PSP)
        return sceUmdCheckMedium();
    #else
        return 0;
    #endif
}

int uxdisc_mount() {
    if (uxdisc_mounted==true) { return false; }
    #if defined(PSP)
        if (uxdisc_check() == true) {
            sceUmdActivate(1, "disc0:");
            sceUmdWaitDriveStat(UMD_WAITFORINIT);
            uxdisc_mounted = true;
            return true;
        }
        return false;
    #else
        return false;
    #endif
}

void uxdisc_init() {
	if (uxdisc_inited) { return; }

    /* ... */

    uxdisc_inited = true;
}

void uxdisc_shutdown() {
    if (not uxdisc_inited) { return; }
}