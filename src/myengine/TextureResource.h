#pragma once
#include "Resource.h"

#include <renderer.h>

namespace myengine
{
	struct MeshRenderer;

	struct TextureResource : Resource
	{
	public:
		TextureResource();
		void onInit();
	private:
		friend struct myengine::MeshRenderer;
		std::shared_ptr<renderer::Texture> m_TextureID;
	};
}