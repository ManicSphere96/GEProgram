#pragma once
#include "Component.h"

namespace myengine
{
	struct Sound;

	struct SoundSource : Component
	{
	public:
		void setClip(std::shared_ptr<Sound> sound) { m_SoundClip = sound; }
		void playClip();
	private:
		std::shared_ptr<Sound> m_SoundClip;
	};
}