// openal_test.cpp : 定义控制台应用程序的入口点。
//
#include "al.h" // for glXzzz
#include "alc.h" // for glcXzzz
#include <stdio.h> // for printf
#include <math.h> // for cosf

#define SHRT_MAX 8192

ALuint Source;// 用于播放声音
ALuint Buffer;// 声音数据

bool InitOpenAL()
{
	ALCdevice * pDevice = alcOpenDevice(NULL);  // 打开默认音频设备
	ALCcontext * pContext = alcCreateContext(pDevice, NULL);
	alcMakeContextCurrent(pContext);
	return true;
	// 注意：这里没有进行失败检测，仅用于示例
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
	// 载入变量.
	const ALsizei size = 800;
	ALsizei freq = 8000;
	ALboolean loop = 1; // 循环播放
	// 使用一段正弦波作数据
	short data[800];
	alGenBuffers(1, &Buffer);
	float max = SHRT_MAX / 4;
	float rad = 0;
	for (int e = 0; e < 800; e++)
	{
		data[e] = (short)(max * cosf(rad));
		rad += 1.f;
	}
	// 载入WAV数据
	alBufferData(Buffer, AL_FORMAT_MONO16, data, size, freq);
	alGenSources(1, &Source);

	// 源声音的位置
	ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
	// 源声音的速度
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
	// 播放
	alSourcePlay(Source);
	printf("Press Enter To Stop Sound\n");
	getchar();
	alSourceStop(Source);
}

int main(int argc, char *argv[])
{
	InitOpenAL();                            // 初始化openal    
	LoadData();                                 // 载入WAV数据
	Play();                                            // 播放
	UnloadData();                             // 卸载WAV数据
	ShutdownOpenAL();                // 关闭openal
	return 0;
}