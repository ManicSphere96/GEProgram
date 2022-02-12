#include "SoundSource.h"
#include "Sound.h"
#include <AL/al.h>

namespace myengine
{
	void SoundSource::playClip()
	{
		ALuint sid = 0;

		alGenSources(1, &sid);

		//alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
		//alSource3f(sid, AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSourcei(sid, AL_BUFFER, m_SoundClip->getBufferId());
		//alSourcef(sid, AL_PITCH, variance);
		//alSourcef(sid, AL_GAIN, vol);
		alSourcePlay(sid);
	}
}