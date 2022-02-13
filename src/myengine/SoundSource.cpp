#include "SoundSource.h"
#include "Sound.h"
#include <AL/al.h>

namespace myengine
{
	void SoundSource::playClip()
	{
		///plays the audioClip given
		ALuint sid = 0;
		alGenSources(1, &sid);
		alSourcei(sid, AL_BUFFER, m_SoundClip->getBufferId());
		alSourcePlay(sid);
	}
}