#include "mesh.h"
#include "renderer.h"

namespace myengine
{
	Mesh::Mesh()
	{}
	void Mesh::onInit()
	{
		
		m_Vao = std::make_shared<renderer::VertexArray>(m_Path + ".obj");
	}
}