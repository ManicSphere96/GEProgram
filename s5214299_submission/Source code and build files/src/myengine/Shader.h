#pragma once
#include <renderer.h>

#include "Resource.h"


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
			/// the storage for the shader program
			std::shared_ptr<renderer::ShaderProgram> m_ShaderProgram;
	};
}