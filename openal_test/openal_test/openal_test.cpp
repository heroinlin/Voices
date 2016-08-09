// openal_test.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "al.h" // for glXzzz
#include "alc.h" // for glcXzzz
#include <stdio.h> // for printf
#include <math.h> // for cosf

#define SHRT_MAX 8192

ALuint Source;// ���ڲ�������
ALuint Buffer;// ��������

bool InitOpenAL()
{
	ALCdevice * pDevice = alcOpenDevice(NULL);  // ��Ĭ����Ƶ�豸
	ALCcontext * pContext = alcCreateContext(pDevice, NULL);
	alcMakeContextCurrent(pContext);
	return true;
	// ע�⣺����û�н���ʧ�ܼ�⣬������ʾ��
}

void ShutdownOpenAL()
{
	ALCcontext *pContext;
	ALCdevice *pDevice;

	pContext = alcGetCurrentContext();
	pDevice = alcGetContextsDevice(pContext);

	alcMakeContextCurrent(NULL);
	alcDestroyContext(pContext);
	alcCloseDevice(pDevice);
}

bool LoadData()
{
	// �������.
	const ALsizei size = 800;
	ALsizei freq = 8000;
	ALboolean loop = 1; // ѭ������
	// ʹ��һ�����Ҳ�������
	short data[800];
	alGenBuffers(1, &Buffer);
	float max = SHRT_MAX / 4;
	float rad = 0;
	for (int e = 0; e < 800; e++)
	{
		data[e] = (short)(max * cosf(rad));
		rad += 1.f;
	}
	// ����WAV����
	alBufferData(Buffer, AL_FORMAT_MONO16, data, size, freq);
	alGenSources(1, &Source);

	// Դ������λ��
	ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
	// Դ�������ٶ�
	ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };

	alSourcei(Source, AL_BUFFER, Buffer);
	alSourcef(Source, AL_PITCH, 1.0f);
	alSourcef(Source, AL_GAIN, 1.0f);
	alSourcefv(Source, AL_POSITION, SourcePos);
	alSourcefv(Source, AL_VELOCITY, SourceVel);
	alSourcei(Source, AL_LOOPING, loop);

	return true;
}
void UnloadData()
{
	alDeleteBuffers(1, &Buffer);
	alDeleteSources(1, &Source);
}

void Play()
{
	// ����
	alSourcePlay(Source);
	printf("Press Enter To Stop Sound\n");
	getchar();
	alSourceStop(Source);
}

int main(int argc, char *argv[])
{
	InitOpenAL();                            // ��ʼ��openal    
	LoadData();                                 // ����WAV����
	Play();                                            // ����
	UnloadData();                             // ж��WAV����
	ShutdownOpenAL();                // �ر�openal
	return 0;
}