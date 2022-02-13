#include "Shader.h"

namespace myengine
{
	Shader::Shader()
	{}

	void Shader::onInit()
	{
		///creates a shader program and stores it here
		m_ShaderProgram = std::make_shared<renderer::ShaderProgram>(m_VertPath + ".txt",m_FragPath + ".txt");
	}
}