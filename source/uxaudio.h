/*
 * uxaudio.h
 * This file is used to manage audio subsystem in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

#ifndef UXAUDIO_H
#define UXAUDIO_H

#include "uxfilesys.h"

//#include "uxaudio/psp.h"
//#include "uxaudio/nds.h"
#include "uxaudio/win.h"
//#include "uxaudio/ps3.h"
//#include "uxaudio/wii.h"

#include "uxaudio/mp3.h"


#ifndef UXAUDIOFILE
	#define UXAUDIOFILE void
#endif

typedef struct UX_AUDIO {
	UXAUDIOFILE * info;									//!< Extra filetype header struct.
	UXFILE * file;										//!< File struct
	
	char * ibuffer;										//!< Input buffer (encoded)
	unsigned int ibufferSize;							//!< Input buffer size.
	short * obuffer;									//!< Output buffer (raw pcm audio)
	unsigned int obufferSize;							//!< Output buffer size.

	int playStatus;										//!< Play state.
	int buffStatus;										//!< Buffer state.
	int loop;											//!< Loop mode.
	int channel;										//!< Playing in channel X.
	
	// extra info.
	int (*load)(struct UX_AUDIO *song);						//!< Load song
	int (*fillBuffer)(struct UX_AUDIO *song);					//!< Fill buffer when needed
	int (*togglePlay)(struct UX_AUDIO *song, int state);		//!< Play / Pause / Stop
	int (*unload)(struct UX_AUDIO *song);						//!< Unload song
} UX_AUDIO;



/* Functions exported by uxaudio module */
extern void uxaudio_init();								//!< Init audio system (if required)
extern void uxaudio_shutdown();							//!< Deinit audio system (if required)

extern UX_AUDIO * uxaudio_load(const char* filename);			//!< Load audio file, return UXAUDIOFILE *
extern void uxaudio_play(UX_AUDIO* song);				//!< Start playing song.
extern void uxaudio_stop(UX_AUDIO* song);				//!< Stop playing song.
extern void uxaudio_pause(UX_AUDIO* song, int toggle);	//!< Pause/resume/toggle song.
extern int uxaudio_playState(UX_AUDIO* song);			//!< Play status: 0-stopped, 1-playing, 2-paused
extern int uxaudio_buffState(UX_AUDIO* song);			//!< Buffer status: 0-not started, 1-buffering, 2-completed

#endif