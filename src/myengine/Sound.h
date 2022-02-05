#pragma once

#include <string>
#include <vector>
#include <AL/al.h>
#include <AL/alc.h>



namespace myengine
{
	struct Sound
	{
		public:
			void loadOgg(std::string fileName, std::vector<char> &buffer, ALenum &format, ALsizei &freq);
		private:
			void onPlay();
			ALint bufferId;
			ALfloat variance;
			ALfloat vol;
	};
}