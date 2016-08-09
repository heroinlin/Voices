#include <al.h>  
#include <alc.h>  
//#include <alu.h>  
#include <alut.h>  
// �洢��������  
ALuint Buffer;

// ���ڲ�������  
ALuint Source;

/*
���ǳ�����ṹ�ĳ�ʼ������OPENAL�����ֲ�ͬ�Ľṹ�����й����������ź�
�������ݴ洢��һ���ڴ��У�Դ��source����ָ��������Ŀռ䡣����Դ�Ƿǳ�
����Ҫ��Դֻ�����ڴ��еı����������ݡ�ԴҲ�����������������λ�ú��ٶȡ�
���������������ߣ��û�������Ψһ�����ߡ�������������Դ���ԣ��������
�����������磬��ͬλ�ý������������ٶȡ�
*/

// Դ������λ��  
ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };

// Դ�������ٶ�  
ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };

// ���ߵ�λ��  
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

// ���ߵ��ٶ�  
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

// ���ߵķ��� (first 3 elements are "at", second 3 are "up")  
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

ALbyte *voicefile = "wave1.wav";

/*
������Ĵ����У����Ƕ�����Դ�����߶����λ�ú��ٶȡ���Щ�����ǻ��ڵ�
���������ʸ�������ܺ������ýṹ��������ͬ�����顣
*/

ALboolean LoadALData()
{
	// �������.  

	ALenum format;
	ALsizei size;
	ALvoid* data;
	//ALsizei freq;
	ALfloat freq;
	ALboolean loop;
	//���������ǽ���һ���������ڴ�һ���ļ��������������ݡ��������ڴ洢�ʺ�  
	//���ǵ�ALUT��Ϣ��  

	// ����WAV����  
	alGenBuffers(1, &Buffer);
	if (alGetError() != AL_NO_ERROR)
		return AL_FALSE;
	//alutLoadWAVFile(voicefile, &format, &data, &size, &freq, &loop);
	alutLoadMemoryFromFile(voicefile, &format, &size,&freq);
	//alBufferData(Buffer, format, data, size, freq);
	//alutUnloadWAV(format, data, size, freq);
	/*
	����alGenBufers���ڽ��������ڴ沢�����Ǵ洢�����Ƕ���ı����С�Ȼ���ж�
	�����Ƿ�洢��
	ALUT��Ϊ���Ǵ��ļ����ṩ���ǽ����ڴ��������Ϣ�����������ǹ�������
	���ݵ��ڴ������������Щ���ݡ�
	*/
	// ����Դ  
	alGenSources(1, &Source);

	if (alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	alSourcei(Source, AL_BUFFER, Buffer);
	alSourcef(Source, AL_PITCH, 1.0f);
	alSourcef(Source, AL_GAIN, 1.0f);
	alSourcefv(Source, AL_POSITION, SourcePos);
	alSourcefv(Source, AL_VELOCITY, SourceVel);
	//alSourcei(Source, AL_LOOPING, loop);
	/*
	�����ý����ڴ����ķ���������Դ����Ȼ�����Ƕ���Դ��������¼�š�
	����Ҫ�����������õ��ڴ档�����Դ����¼�š���ˣ�����ֻ����������ͬʱ��
	����Ҳ���������Ƕ����Դλ�ú��ٶȡ�
	*/
	// �������Ⲣ����  
	if (alGetError() == AL_NO_ERROR)
		return AL_TRUE;

	return AL_FALSE;
	//�ں����Ľ�β�����ǽ�������ļ�⣬��ȷ��������ȷ��  
}
void SetListenervalues()
{
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}
//���ǽ���һ���������ڸ��������ٶȡ�  
void KillALData()
{
	alDeleteBuffers(1, &Buffer);
	alDeleteSources(1, &Source);
	alutExit();
}
//����һ���رպ����������ͷ��ڴ����Ƶ�豸��  