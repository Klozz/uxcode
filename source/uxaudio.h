#ifndef UXAUDIO_H
#define UXAUDIO_H

//#include "uxaudio/psp.h"
//#include "uxaudio/nds.h"
#include "uxaudio/win.h"
//#include "uxaudio/ps3.h"
//#include "uxaudio/wii.h"


#ifndef UXAUDIOFILE
	#define UXAUDIOFILE void
#endif

typedef struct UX_AUDIO {
	UXAUDIOFILE * audio;								//!< Pointer to audio stream / object.
	void * file;										//!< Pointer to file.
	int fileType;										//!< File type.
	int playStatus;										//!< Play state.
	int buffStatus;										//!< Buffer state.
	int loop;											//!< Loop mode.
	int channel;										//!< Playing in channel X.
	// extra info.
} UX_AUDIO;



/* Functions exported by uxaudio module */
extern void uxaudio_init();								//!< Init audio system (if required)
extern void uxaudio_shutdown();							//!< Deinit audio system (if required)

extern UX_AUDIO * uxaudio_load(char* filename);			//!< Load audio file, return UXAUDIOFILE *
extern void uxaudio_play(UX_AUDIO* song);				//!< Start playing song.
extern void uxaudio_stop(UX_AUDIO* song);				//!< Stop playing song.
extern void uxaudio_pause(UX_AUDIO* song, int toggle);	//!< Pause/resume/toggle song.
extern int uxaudio_playState(UX_AUDIO* song);			//!< Play status: 0-stopped, 1-playing, 2-paused
extern int uxaudio_buffState(UX_AUDIO* song);			//!< Buffer status: 0-not started, 1-buffering, 2-completed

#endif