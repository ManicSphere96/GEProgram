#include "Sound.h"
#include "stb_vorbis.h"

namespace myengine
{
	void Sound::onInit()
	{
		///sets up sound from a path

		ALenum format = 0;
		ALsizei freq = 0;
		std::vector<char> bufferData;

		loadOgg(m_Path + ".ogg", bufferData, format, freq);

		alGenBuffers(1, &m_BufferId);

		alBufferData(m_BufferId, format, &bufferData.at(0), static_cast<ALsizei>(bufferData.size()), freq);
	}

	void Sound::loadOgg(std::string fileName, std::vector<char>& buffer, ALenum& format, ALsizei& freq)
	{
		
		///Loads an ogg file with a provided path using the string parameter
		

		int channels = 0;
		int sampleRate = 0;
		short* output = NULL;

		size_t samples = stb_vorbis_decode_filename(fileName.c_str(),
			&channels, &sampleRate, &output);

		samples = samples - samples % 4;

		if (samples == -1)
		{
			throw std::exception(std::string("Failed to open file '" + fileName + "' for decoding").c_str());
		}

		if (channels == 1)
		{
			format = AL_FORMAT_MONO16;
		}
		else
		{
			format = AL_FORMAT_STEREO16;
		}

		freq = sampleRate;

		buffer.resize(samples * 2);
		memcpy(&buffer.at(0), output, buffer.size());

		free(output);
	}
}