#include <conio.h>  
#include <stdlib.h>  
#include<stdio.h>
#include <al.h>  
#include <alc.h>  
//#include <alu.h>  
#include <alut.h>  
#include "voice_load.h"

/*********************************************************************************
This is the interesting part of the tutorial. It's a very basic loop that lets us
control the playback of the audio sample. Pressing 'p' will replay the sample,
pressing 's' will stop the sample, and pressing 'h' will pause the sample.
Pressing 'q' will exit the program.
*********************************************************************************/



int main(int argc, char *argv[])
{
	// 初始OPENAL并清错误字节  

	alutInit(&argc, argv);
	alGetError();
	/*
	函数alutInit将安装ALC需要的东西。ALUT通过ALC并设置她为当前建立OPENAL
	环境描述。在WINDOWS平台上初始DIRECTSOUND。然后用‘GLGETERROR’检测错误。
	*/
	// 载入WAV数据  
	if (LoadALData() == AL_FALSE)
		return -1;

	SetListenervalues();

	// 设置退出函数  
	atexit(KillALData);

	//我们将检测WAV文件是否正确载入。如果没有退出程序。正确后，更新听者参数，最后退出。  
	ALubyte c = ' ';

	while (c != 'q')
	{
		c = getchar();

		switch (c)
		{
			// Pressing 'p' will begin playing the sample.  
		case 'p': alSourcePlay(Source); break;

			// Pressing 's' will stop the sample from playing.  
		case 's': alSourceStop(Source); break;

			// Pressing 'h' will pause (hold) the sample.  
		case 'h': alSourcePause(Source); break;
		};
	}

	return 0;
}

