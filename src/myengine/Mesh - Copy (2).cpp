#include "mesh.h"
#include "renderer.h"

namespace myengine
{
	Mesh::Mesh()
	{}
	void Mesh::onInit()
	{
		
		vao = std::make_shared <renderer::VertexArray>(m_Path + ".obj");
	}
}