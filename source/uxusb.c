/*
 * uxusb.c
 * This file is used to manage usb subsystem in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */
#include "utils.h"

int uxusb_modules_loaded = false;
int uxusb_usb_active = false;

#ifdef PSP
SceUID modules[8];
#define PSP_USBSTOR_UID 0x1C8
#endif

int uxusb_status() {
	#ifdef PSP
		return sceUsbGetState();
	#endif
}

void uxusb_init() {
	#ifdef PSP
		if (uxusb_modules_loaded == false) {
			modules[0] = pspSdkLoadStartModule("flash0:/kd/chkreg.prx", PSP_MEMORY_PARTITION_KERNEL);
			modules[1] = pspSdkLoadStartModule("flash0:/kd/npdrm.prx", PSP_MEMORY_PARTITION_KERNEL);
			modules[2] = pspSdkLoadStartModule("flash0:/kd/semawm.prx", PSP_MEMORY_PARTITION_KERNEL);
			modules[3] = pspSdkLoadStartModule("flash0:/kd/usbstor.prx", PSP_MEMORY_PARTITION_KERNEL);
			modules[4] = pspSdkLoadStartModule("flash0:/kd/usbstormgr.prx", PSP_MEMORY_PARTITION_KERNEL);
			modules[5] = pspSdkLoadStartModule("flash0:/kd/usbstorms.prx", PSP_MEMORY_PARTITION_KERNEL);
			modules[6] = pspSdkLoadStartModule("flash0:/kd/usbstorboot.prx", PSP_MEMORY_PARTITION_KERNEL);
			modules[7] = pspSdkLoadStartModule("flash0:/kd/usbdevice.prx", PSP_MEMORY_PARTITION_KERNEL);
			uxusb_modules_loaded = true;
		}
		if (uxusb_usb_active == false) {
    		sceUsbStart(PSP_USBBUS_DRIVERNAME, 0, 0);
    		sceUsbStart(PSP_USBSTOR_DRIVERNAME, 0, 0);
    		sceUsbstorBootSetCapacity(0x800000);
    		sceUsbActivate(PSP_USBSTOR_UID);
    		uxusb_usb_active = true;
    	}
    #endif
}

void uxusb_shutdown() {
	#ifdef PSP
		if (uxusb_usb_active == true) {
			sceUsbDeactivate(PSP_USBSTOR_UID);
			sceIoDevctl("fatms0:", 0x0240D81E, NULL, 0, NULL, 0 );			// Fake re-insertion of MS.
			sceUsbStop(PSP_USBSTOR_DRIVERNAME, 0, 0);
			sceUsbStop(PSP_USBBUS_DRIVERNAME, 0, 0);
			uxusb_usb_active = false;
		}
		if (uxusb_modules_loaded == true) {
			if ((modules[7] & 0x80000000) == 0) { sceKernelStopModule(modules[7], 0, NULL, NULL, NULL); sceKernelUnloadModule(modules[7]); }
			if ((modules[6] & 0x80000000) == 0) { sceKernelStopModule(modules[6], 0, NULL, NULL, NULL); sceKernelUnloadModule(modules[6]); }
			if ((modules[5] & 0x80000000) == 0) { sceKernelStopModule(modules[5], 0, NULL, NULL, NULL); sceKernelUnloadModule(modules[5]); }
			if ((modules[4] & 0x80000000) == 0) { sceKernelStopModule(modules[4], 0, NULL, NULL, NULL); sceKernelUnloadModule(modules[4]); }
			if ((modules[3] & 0x80000000) == 0) { sceKernelStopModule(modules[3], 0, NULL, NULL, NULL); sceKernelUnloadModule(modules[3]); }
			if ((modules[2] & 0x80000000) == 0) { sceKernelStopModule(modules[2], 0, NULL, NULL, NULL); sceKernelUnloadModule(modules[2]); }
			if ((modules[1] & 0x80000000) == 0) { sceKernelStopModule(modules[1], 0, NULL, NULL, NULL); sceKernelUnloadModule(modules[1]); }
			if ((modules[0] & 0x80000000) == 0) { sceKernelStopModule(modules[0], 0, NULL, NULL, NULL); sceKernelUnloadModule(modules[0]); }
			uxusb_modules_loaded = false;
		}
	#endif
}