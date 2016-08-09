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
	// ��ʼOPENAL��������ֽ�  

	alutInit(&argc, argv);
	alGetError();
	/*
	����alutInit����װALC��Ҫ�Ķ�����ALUTͨ��ALC��������Ϊ��ǰ����OPENAL
	������������WINDOWSƽ̨�ϳ�ʼDIRECTSOUND��Ȼ���á�GLGETERROR��������
	*/
	// ����WAV����  
	if (LoadALData() == AL_FALSE)
		return -1;

	SetListenervalues();

	// �����˳�����  
	atexit(KillALData);

	//���ǽ����WAV�ļ��Ƿ���ȷ���롣���û���˳�������ȷ�󣬸������߲���������˳���  
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

