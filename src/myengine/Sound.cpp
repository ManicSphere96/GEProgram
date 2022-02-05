#include "Sound.h"
#include "stb_vorbis.c"

namespace myengine
{
	void Sound::loadOgg(std::string fileName, std::vector<char>& buffer, ALenum& format, ALsizei& freq)
	{
		/**
		 * \brief Loads an ogg file with a provided
		 * path using the string parameter
		 */

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

	void Sound::onPlay()
	{
		ALuint sid = 0;
		alGenSources(1, &sid);

		//alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
		//alSource3f(sid, AL_POSITION, 0.0f, 0.0f, 0.0f);
		//alSourcei(sid, AL_BUFFER, bufferId);
		//alSourcef(sid, AL_PITCH, variance);
		//alSourcef(sid, AL_GAIN, vol);
		alSourcePlay(sid);
	}
}