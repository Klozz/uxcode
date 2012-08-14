/*
 * uxaudio.c
 * This file is used to manage audio subsystem in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */
#include "utils.h"

void uxaudio_init() {
	#ifdef _WIN32
		FSOUND_Init (44100, 16, 0);
		FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(), 1);
	#endif
}

void uxaudio_shutdown() {
	// finalize sound system.
}



UX_AUDIO * uxaudio_load(char* filename) {
	// try opening filename
	
	// try determine filetype or encoding
	
	// malloc UX_AUDIO structure
	
	// fill UX_AUDIO structure
	
	// open file
	
	// return pointer
	
	return NULL;
}

void uxaudio_play(UX_AUDIO* song) {
	if (song == NULL) return;
	if (uxaudio_playState(song) == 1) return;
	
}

void uxaudio_stop(UX_AUDIO* song) {
	if (song == NULL) return;
	if (uxaudio_playState(song) == 0) return;
	
}

void uxaudio_pause(UX_AUDIO* song, int toggle) {
	if (song != NULL) { return; }
	if (uxaudio_playState(song) == 0 and (toggle == 1 or toggle == 2)) {
		uxaudio_play(song);
		return;
	}
	if (uxaudio_playState(song) == 1 and (toggle == 0 or toggle == 2)) {
		uxaudio_stop(song);
		return;
	}
}

int uxaudio_playState(UX_AUDIO* song) {
	return song->playStatus;
}

int uxaudio_buffState(UX_AUDIO* song) {
	return song->buffStatus;
}