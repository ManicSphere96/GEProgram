#include "Model.h"

namespace myengine
{
	void Model::onInit()
	{
		vao = std::make_shared <renderer::VertexArray>(getPath() + ".obj");
	}
}