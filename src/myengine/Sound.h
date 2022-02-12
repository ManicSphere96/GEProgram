#pragma once

#include <string>
#include <vector>
#include <AL/al.h>
#include <AL/alc.h>
#include "Resource.h"



namespace myengine
{
	struct SoundSource;

	struct Sound : Resource
	{
	public:
		void onInit();
		void loadOgg(std::string fileName, std::vector<char>& buffer, ALenum& format, ALsizei& freq);
		ALuint getBufferId() { return m_BufferId; }
	private:
		friend struct myengine::SoundSource;
		ALuint m_BufferId;
		ALfloat m_Variance;
		ALfloat m_Vol;
	};
}