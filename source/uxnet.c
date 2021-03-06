/*
 * uxnet.c
 * This file is used to manage network in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#include "utils.h"

void uxnet_init() {
	#ifdef PSP
		SceUID modules[6];
    	modules[0] = sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
    	modules[1] = sceUtilityLoadNetModule(PSP_NET_MODULE_INET);
    	modules[2] = sceUtilityLoadNetModule(PSP_NET_MODULE_PARSEURI);
    	modules[3] = sceUtilityLoadNetModule(PSP_NET_MODULE_PARSEHTTP);
    	modules[4] = sceUtilityLoadNetModule(PSP_NET_MODULE_HTTP);
    	modules[5] = sceUtilityLoadNetModule(PSP_NET_MODULE_SSL);
    #endif 
}

void uxnet_shutdown() {

}