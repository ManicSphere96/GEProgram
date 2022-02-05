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

		vbo = std::make_shared<renderer::VertexBuffer>();
		vbo->add(glm::vec3(0.0f, 0.5f, 0.0f));
		vbo->add(glm::vec3(-0.5f, -0.5f, 0.0f));
		vbo->add(glm::vec3(0.5f, -0.5f, 0.0f));

		vao = std::make_shared<renderer::VertexArray>();

		vao->setBuffer(0, vbo);
		vao->getId();

		shaderProgram = std::make_shared<renderer::ShaderProgram>("../Assets/Shaders/vertShader.txt", "../Assets/Shaders/fragShader.txt");

		getTransform()->setPosition(glm::vec3(0, 0, -2.5f));

		std::cout << "Displaying..." << std::endl;
	}

	void TriangleRenderer::onDisplay()
	{	
		shaderProgram->setUniform("u_Model", getTransform()->getModel());

		shaderProgram->draw(vao);
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