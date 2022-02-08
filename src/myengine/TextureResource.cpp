#include "TextureResource.h"

namespace myengine
{
	TextureResource::TextureResource()
	{}

	void TextureResource::onInit()
	{
		m_TextureID = std::make_shared<renderer::Texture>(m_Path + ".png");
	}
}