/*
 * mp3.c
 * This file is used to manage MP3 fileformat in the UXcode library.
 * uxcode Version 0.1 by DeViaNTe - http://www.gcrew.es
 *
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 */

int uxaudio_loadMP3(UX_AUDIO *song) {
	#if defined(PSP)
		sceMp3InitResource();
		UX_AUDIO_MP3H * mp3info = (song->info);

		SceMp3InitArg mp3Init;
		mp3Init.mp3StreamStart = 0;
		mp3Init.mp3StreamEnd = (song->file)->filesize;
		mp3Init.unk1 = 0;
		mp3Init.unk2 = 0;
		mp3Init.mp3Buf = song->ibuffer;
		mp3Init.mp3BufSize = song->ibufferSize;
		mp3Init.pcmBuf = song->obuffer;
		mp3Init.pcmBufSize = song->obufferSize;

		mp3info->mp3handle = sceMp3ReserveMp3Handle( &mp3Init );
		if (mp3info->mp3handle < 0) { return -1; }
		if (song->fillBuffer(song) != 1) { sceMp3ReleaseMp3Handle( mp3info->mp3handle ); return -1; }
		mp3info->bitrate = sceMp3GetBitRate( mp3info->mp3handle );
		mp3info->samplerate = sceMp3GetSamplingRate( mp3info->mp3handle );
		mp3info->channels = sceMp3GetMp3ChannelNum( mp3info->mp3handle );
	#endif
	return 0;
}

int uxaudio_fillBufferMP3(UX_AUDIO *song) {
	#if defined(PSP)
		UX_AUDIO_MP3H * mp3info = (song->info);
		int write;
		int pos;
		int status = sceMp3GetInfoToAddStreamData( mp3info->mp3handle, (unsigned char**)&(song->ibuffer), &write, &pos);
		if (status < 0) { return 0; }
		status = uxfseek( song->file , pos, SEEK_SET );
		if (status < 0) { return 0; }
		int read = uxfread( song->file, song->ibuffer, write );
		if (read < 0 || read == 0) { return 0; }
		status = sceMp3NotifyAddStreamData( mp3info->mp3handle , read );
		if (status < 0) { return 0; }
		return (pos > 0);
	#endif
	return 0;
}

int uxaudio_togglePlayMP3(UX_AUDIO *song, int state) {

	return 0;
}

int uxaudio_unloadMP3(UX_AUDIO *song) {

	return 0;
}