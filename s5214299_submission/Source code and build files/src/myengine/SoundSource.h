#pragma once
#include "Component.h"

namespace myengine
{
	struct Sound;

	struct SoundSource : Component
	{
	public:
		/// sets the sound clip to play when play clip is called
		void setClip(std::shared_ptr<Sound> sound) { m_SoundClip = sound; }
		void playClip();
	private:
		/// the sound clip ready to be played
		std::shared_ptr<Sound> m_SoundClip;
	};
}