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
		/// Returns the Sound BufferID
		ALuint getBufferId() { return m_BufferId; }
	private:
		friend struct myengine::SoundSource;
		/// the sound buffer ID
		ALuint m_BufferId;
		/// the sound variance
		ALfloat m_Variance;
		/// the sound volume
		ALfloat m_Vol;
	};
}