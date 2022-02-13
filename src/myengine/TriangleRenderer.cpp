#include "TriangleRenderer.h"
#include "Transform.h"
#include "Keyboard.h"
#include "Environment.h"
#include <vector>

namespace myengine
{
	TriangleRenderer::~TriangleRenderer()
	{

	}

	void TriangleRenderer::onInit()
	{
		std::cout << "Initializing..." << std::endl;

		m_Vbo = std::make_shared<renderer::VertexBuffer>();
		m_Vbo->add(glm::vec3(0.0f, 0.5f, 0.0f));
		m_Vbo->add(glm::vec3(-0.5f, -0.5f, 0.0f));
		m_Vbo->add(glm::vec3(0.5f, -0.5f, 0.0f));
		
		m_Vao = std::make_shared<renderer::VertexArray>();
		
		m_Vao->setBuffer(0, m_Vbo);
		m_Vao->getId();

		m_ShaderProgram = std::make_shared<renderer::ShaderProgram>("../Assets/Shaders/vertShader.txt", "../Assets/Shaders/fragShader.txt");

		getTransform()->setPosition(glm::vec3(0, 0, -2.5f));

		std::cout << "Displaying..." << std::endl;
	}

	void TriangleRenderer::onDisplay()
	{	
		m_ShaderProgram->setUniform("u_Model", getTransform()->getModel());

		m_ShaderProgram->draw(m_Vao);
	}

	void TriangleRenderer::onTick()
	{
		if (getKeyboard()->isKeyDown(SDLK_UP))
		{
			getTransform()->move(glm::vec3(0, 0, -1.5f) * getEnvironment()->getDeltaTime());
		}

		if (getKeyboard()->isKeyDown(SDLK_DOWN))
		{
			getTransform()->move(glm::vec3(0, 0, 1.5f) * getEnvironment()->getDeltaTime());
		}
		
		if (getKeyboard()->isKeyDown(SDLK_RIGHT))
		{
			getTransform()->move(glm::vec3(1.5f, 0, 0) * getEnvironment()->getDeltaTime());
		}
		
		if (getKeyboard()->isKeyDown(SDLK_LEFT))
		{
			getTransform()->move(glm::vec3(-1.5f, 0, 0) * getEnvironment()->getDeltaTime());
		}
	}
	
}