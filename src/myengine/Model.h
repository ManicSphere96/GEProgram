#pragma once


#include <iostream>
#include <string>
#include <GL/glew.h>
#include <renderer.h>
#include "Resource.h"
#include "Component.h"
namespace myengine
{
	struct MeshRenderer;

	struct Model : Resource , Component
	{
		public:
			void onInit();
		private:
			friend struct myengine::MeshRenderer;
			std::shared_ptr<renderer::VertexArray> vao;
	};
}