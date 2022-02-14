#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <renderer.h>
#include "Resource.h"

namespace myengine
{
	struct MeshRenderer;

	struct Mesh : Resource
	{
	public:
		Mesh();
		void onInit();
		///Returns the VAO
		std::shared_ptr<renderer::VertexArray> getVao() { return m_Vao;  }
	private:
		friend struct myengine::MeshRenderer;
		///Holds the vao generated on Init
		std::shared_ptr<renderer::VertexArray> m_Vao;
	};
}