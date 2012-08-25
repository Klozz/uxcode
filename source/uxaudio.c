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

#include "uxaudio/mp3.c"

void uxaudio_init() {
	#ifdef _WIN32
		FSOUND_Init (44100, 16, 0);
		FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(), 1);
	#elif defined(PSP)
		int status = sceUtilityLoadModule(PSP_MODULE_AV_AVCODEC);
		status = sceUtilityLoadModule(PSP_MODULE_AV_MP3);
	#endif
}

void uxaudio_shutdown() {
	#ifdef _WIN32
		FSOUND_Close();
	#elif defined(PSP)
		int status = sceUtilityUnloadModule(PSP_MODULE_AV_MP3);
		sceUtilityUnloadModule(PSP_MODULE_AV_AVCODEC);
	#endif
}



UX_AUDIO * uxaudio_load(const char* file) {
	UX_AUDIO * aud = NULL;
	u32 extlen = 0;
	UXFILE * f = NULL;

	/* File exists */
	if ( (f = uxfopen(file,"rb",UX_F_NORMAL)) == NULL ) { return NULL; }
	
	/* Init UX_AUDIO struct */
	aud = (UX_AUDIO *)uxmemalloc(sizeof(UX_AUDIO));
	uxmemset(aud,0,sizeof(UX_AUDIO));
	aud->file = f;
	aud->channel = -1;
	aud->ibuffer = (char *)uxmemalloc(16 << 10);
	aud->ibufferSize = 16 << 10;
	aud->obuffer = (short *)uxmemalloc(9 << 10);
	aud->obufferSize = 9 << 10;
	
	/* By filetype: */
	if ( !strncmp(uxstring_lower(uxfile_ext((char *)file,&extlen)),"mp3",3) ) {
		aud->info = (UX_AUDIO_MP3H *)uxmemalloc(sizeof(UX_AUDIO_MP3H));
		aud->load = &uxaudio_loadMP3;
		aud->fillBuffer = &uxaudio_fillBufferMP3;
		aud->togglePlay = &uxaudio_togglePlayMP3;
		aud->unload = &uxaudio_unloadMP3;
	}

	/* Try if all worked */
	if (aud->load != NULL && aud->load(aud) == 0) { return aud; }

	uxmemfree(aud); 
	uxfclose(f);
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