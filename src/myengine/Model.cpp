#include "Model.h"

namespace myengine
{
	Model::Model()
	{

	}
	void Model::onInit(const std::string path)
	{
		Resource::onInit(path);
		vao = std::make_shared <renderer::VertexArray>(path + ".obj");
	}
}