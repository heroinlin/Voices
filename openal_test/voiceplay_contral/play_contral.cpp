#include <conio.h>  
#include <stdlib.h>  
#include<stdio.h>
#include <al.h>  
#include <alc.h>  
//#include <alu.h>  
#include <alut.h>  
#include "voice_load.h"
ALuint alSource;
ALuint source;
ALsizei size2;
ALsizei frequent;
ALenum format;
int main(int argc,char**argv)
{
	char *voice_path = argv[1];
	alcMakeContextCurrent(alcCreateContext(alcOpenDevice(NULL), NULL));

	//openal≤•∑≈“Ù∆µ1
	loadWavFile(voice_path, &alSource, &size2, &frequent, &format);
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, alSource);
	alSourcePlay(source);
	ALubyte c = ' ';
	printf("Press Enter h To Pause \np To Begin\ns To Stop Sound\n ");
	while (c != 'q')
	{
		c = getchar();

		switch (c)
		{
			// Pressing 'p' will begin playing the sample.  
		case 'p': alSourcePlay(source); break;

			// Pressing 's' will stop the sample from playing.  
		case 's': alSourceStop(source); break;

			// Pressing 'h' will pause (hold) the sample.  
		case 'h': alSourcePause(source); break;
		};
	}
	return 0;
}

