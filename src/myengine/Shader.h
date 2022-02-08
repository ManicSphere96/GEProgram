#pragma once
#include "Resource.h"

#include <renderer.h>

namespace myengine
{
	struct MeshRenderer;

	struct Shader : Resource
	{
		public:
			Shader();
			void onInit();
		private:
			friend struct myengine::MeshRenderer;
			std::shared_ptr<renderer::ShaderProgram> m_ShaderProgram;
	};
}