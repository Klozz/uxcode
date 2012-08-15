/*
 * uxdisc.c
 * This file is used to manage discs and other removable media in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */
#include "utils.h"

int uxdisc_inited  = false;
int uxdisc_mounted = false;

int uxdisc_waitfordisc() {
	#if defined(PSP)
		if (uxdisc_check() == false) { sceUmdWaitDriveStat(PSP_UMD_PRESENT); }
	#endif
	return 0;
}

int uxdisc_check() {
	#if defined(PSP)
		return (sceUmdCheckMedium() != 0);
	#else
		return false;
	#endif
}

int uxdisc_mount() {
	if (uxdisc_mounted==true) { return false; }

	#if defined(PSP)
		int status;
		if (uxdisc_check() == true) {
			sceUmdActivate(1, "disc0:");
			status = sceUmdWaitDriveStatWithTimer(UMD_WAITFORINIT, 5000000); // 5 secs timeout.
			uxdisc_mounted = (status >= 0);
			return (uxdisc_mounted==true);
		}
		return false;
	#else
		return false;
	#endif
}

int uxdisc_unmount() {
	if (uxdisc_mounted==false) { return false; }

	#if defined(PSP)
		int status;
		status = sceUmdDeactivate(1,"disc0:");
		uxdisc_mounted = (status >= 0);
		return (uxdisc_mounted==false);
	#else
		return false;
	#endif
}

void uxdisc_init() {
	if (uxdisc_inited) { return; }
	uxdisc_mount();
	uxdisc_inited = true;
}

void uxdisc_shutdown() {
	if (not uxdisc_inited) { return; }
	uxdisc_unmount();
	uxdisc_inited = false;
}