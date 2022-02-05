#pragma once
#include "Resource.h"

#include <renderer/renderer.h>
#include <iostream>
#include <string>
#include <GL/glew.h>

namespace myengine
{
	struct MeshRenderer;

	struct Model : Resource
	{
		public:
			void onInit();
		private:
			friend struct myengine::MeshRenderer;
			std::shared_ptr<renderer::VertexArray> vao;
	};
}