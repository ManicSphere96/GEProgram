#pragma once

#include <iostream>
#include <GL/glew.h>

#include <renderer.h>

#include "Component.h"

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
			std::shared_ptr<renderer::ShaderProgram> m_ShaderProgram;
			std::shared_ptr<renderer::VertexBuffer> m_Vbo;
			std::shared_ptr<renderer::VertexArray> m_Vao;
	};
}