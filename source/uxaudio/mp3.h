/*
 * mp3.h
 * This file is used to manage MP3 fileformat in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

typedef struct UX_AUDIO_MP3H {
	#if defined(PSP)
		SceInt32 mp3handle;
	#endif
	unsigned int bitrate;
	unsigned int samplerate;
	unsigned int channels;
} UX_AUDIO_MP3H;