#pragma once
#include "Component.h"

#include <renderer.h>
#include <iostream>
#include <GL/glew.h>

namespace myengine
{
	struct TriangleRenderer : Component
	{
		public:
			~TriangleRenderer();
			void onInit();
		private:
			void onDisplay();
			void onTick();
			std::shared_ptr<renderer::ShaderProgram> shaderProgram;
			std::shared_ptr<renderer::VertexBuffer> vbo;
			std::shared_ptr<renderer::VertexArray> vao;
	};
}