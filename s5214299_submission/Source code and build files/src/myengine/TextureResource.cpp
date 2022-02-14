#include "TextureResource.h"

namespace myengine
{
	TextureResource::TextureResource()
	{}

	void TextureResource::onInit()
	{
		///creates a tecture object and saves it
		m_TextureID = std::make_shared<renderer::Texture>(m_Path + ".png");
	}
}