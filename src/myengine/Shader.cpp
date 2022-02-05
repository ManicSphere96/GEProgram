#include "Shader.h"

namespace myengine
{
	void Shader::onInit()
	{
		shaderProgram = std::make_shared<renderer::ShaderProgram>(getPath() + ".vert",
			getPath() + ".frag");
	}
}