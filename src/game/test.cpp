#include "test.h"



void Test111::onInit()
{
		m_MeshRenderer = getEntity()->addComponent<MeshRenderer>();
		m_MeshRenderer->setMesh(getComponent<Model>());
		m_MeshRenderer->getTransform()->setPosition(glm::vec3(0, 0, -10));
		m_MeshRenderer->getTransform()->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
		m_MeshRenderer->getTransform()->rotate(glm::vec3(0, 90.0f, 0));
		m_ShaderProgram = std::make_shared<renderer::ShaderProgram>("Debug\\vertShader.txt", "Debug\\fragShader.txt" );
		m_MeshRenderer->setShader(m_ShaderProgram);
		m_MeshRenderer->onDisplay();
}