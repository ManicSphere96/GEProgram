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

	private:
		friend struct myengine::MeshRenderer;
		std::shared_ptr<renderer::VertexArray> vao;
	};
}