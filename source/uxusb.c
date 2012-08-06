#include "utils.h"

void uxusb_init() {
	#ifdef PSP
		SceUID modules[8];
    	modules[0] = pspSdkLoadStartModule("flash0:/kd/chkreg.prx", PSP_MEMORY_PARTITION_KERNEL);
    	modules[1] = pspSdkLoadStartModule("flash0:/kd/npdrm.prx", PSP_MEMORY_PARTITION_KERNEL);
    	modules[2] = pspSdkLoadStartModule("flash0:/kd/semawm.prx", PSP_MEMORY_PARTITION_KERNEL);
    	modules[3] = pspSdkLoadStartModule("flash0:/kd/usbstor.prx", PSP_MEMORY_PARTITION_KERNEL);
    	modules[4] = pspSdkLoadStartModule("flash0:/kd/usbstormgr.prx", PSP_MEMORY_PARTITION_KERNEL);
    	modules[5] = pspSdkLoadStartModule("flash0:/kd/usbstorms.prx", PSP_MEMORY_PARTITION_KERNEL);
    	modules[6] = pspSdkLoadStartModule("flash0:/kd/usbstorboot.prx", PSP_MEMORY_PARTITION_KERNEL);
		modules[7] = pspSdkLoadStartModule("flash0:/kd/usbdevice.prx", PSP_MEMORY_PARTITION_KERNEL); 
    #endif 
}

void uxusb_shutdown() {

}