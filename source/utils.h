#ifndef LUADEVUTILSH
#define LUADEVUTILSH

#define GLUT_BUILDING_LIB
#define GLUT_DISABLE_ATEXIT_HACK
#define __WATCOMC__

#define and                    &&
#define or                     ||
#define bitand                 &
#define bitor                  |
#define complement             ~
#define not                    !
#define xor                    ^
#define true                   1
#define false                  0
#define PI                     3.14159265
#define clamp(val, min, max)   ((val)>(max)?(max):((val)<(min)?(min):(val)))                                                 //!< Constrain a value between min and max.
#define min(x, y)              (((x) < (y)) ? (x) : (y))                                                                     //!< Minimum value
#define max(x, y)              (((x) > (y)) ? (x) : (y))                                                                     //!< Maximum value
#define intswap(a)             (((a & (0xFF<<24))>>24) | ((a & (0xFF<<16))>>8) | ((a & (0xFF<<8))<<8) | ((a & (0xFF))<<24))  //!< Byteswap 32b
#define shortswap(a)           (((a & 0xFF00)>>8) | ((a & (0xFF))<<8))															//!< Byteswap 16b

/* MESSAGES RETURNED */
#define UX_MSG_CNT_OPN 1
#define UX_MSG_NOT_MEM 2
#define UX_MSG_NOT_SUP 3
#define UX_MSG_TOO_BIG 4
#define UX_MSG_OK      0

typedef unsigned long DWORD;
typedef unsigned short WORD;

/* Platform dependent defines */
#if defined(WII)

	#include <stdio.h>
	#include <unistd.h>
	#include <dirent.h>
	#include <string.h>
	#include <stdlib.h>
	#include <ctype.h>
	
	#include <fat.h>                // FAT library.
	#include <sdcard/gcsd.h>        // Gamecube sd card
	#include <sdcard/wiisd_io.h>    // sd card
	
	#include <gccore.h>             // Gamecube libraries
	#include <ogc/pad.h>            // Gamecube pads
	#include <wiiuse/wpad.h>        // Wiimotes & expansions
	#include <mii.h>                // miis
	
#elif defined(PSP)
	
	#define sleep _sleep 
	
	#include <stdio.h>
	#include <unistd.h>
	#include <string.h>
	#include <stdlib.h>
	
	#include <fcntl.h>
	#include <malloc.h>
	#include <time.h>
	#include <machine/fastmath.h>
	
	#include <pspsdk.h>
	#include <psptypes.h>
	#include <psputils.h>
	#include <pspdisplay_kernel.h>
	#include <psploadexec.h>
	#include <pspkernel.h>
	#include <pspctrl.h>
	#include <psprtc.h>
	
	#include <sys/unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	
	#include <kubridge.h>
	#include <systemctrl.h>
	#include <systemctrl_se.h>
	#include <pspsyscon.h>
	
	#include <pspaudio.h>
	#include <pspaudiolib.h>
	
	#include <pspusb.h>
	#include <pspusbcam.h>
	#include <pspusbstor.h>
	#include <pspusbacc.h>
	#include <pspusbdevice.h>
	
	#include <pspumd.h>
	
	#include <pspopenpsid.h>
	#include <psputility.h>
	
	#include <psppower.h>
	#include <pspdebug.h>
	
	#include <pspiofilemgr.h>
	
	#include <pspuser.h>
	
	#include <pspdisplay.h>
	#include <pspgu.h>
	#include <pspgum.h>
	
	#include <pspvideocodec.h>
	#include <pspmpegbase.h>
	
	#include <pspjpeg.h>
	
	#include <psphprm.h>
	
	#include <arpa/inet.h>
	#include <pspwlan.h>
	#include <pspnet_apctl.h>
	#include <pspnet_resolver.h>
	#include <psphttp.h>
	#include <psputility_htmlviewer.h>
	#include <psputility_avmodules.h>
	#include <psputility_usbmodules.h>

#elif defined(_WIN32)
    
	#define GLUT_BUILDING_LIB
	#define GLUT_DISABLE_ATEXIT_HACK
	#define __WATCOMC__
	
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	
	#include <windows.h>
	
	#include <GL/glew.h>
	#include <GL/freeglut.h>
	
	#include <fmod/fmod.h>
	
#elif defined(NDS)

#elif defined(UNIX)

#endif

/* UXCODE DEFINES */
#include "uxcontrols.h"
#include "uxmem.h"
//#include "uxstrings.h"
#include "uxcode.h"
#include "uxfilesys.h"
#include "uxmath.h"
#include "uxgraphics.h"
#include "uxrtc.h"
#include "uxaudio.h"
//#include "uxtime.h"
//#include "uxluaapi.h"
//#include "uxjsapi.h"

#endif
