#include "mesh.h"
#include "renderer.h"

namespace myengine
{
	Mesh::Mesh()
	{}
	void Mesh::onInit()
	{
		///creates a  Vertex Array Object from a path and stores it.
		m_Vao = std::make_shared<renderer::VertexArray>(m_Path + ".obj");
	}
}