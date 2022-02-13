#include "MeshRenderer.h"
#include "Model.h"
#include "Shader.h"
#include "Transform.h"


#include <renderer.h>

namespace myengine
{
	void MeshRenderer::setVisible(bool visible)
	{
		m_IsVisible = visible;
	}

	void MeshRenderer::onDisplay()
	{
		if (m_IsVisible)
		{
			// Light Positions used for PBR 
			glm::vec3 lightPositions[] =
			{
				glm::vec3(-10.0f, 10.0f, 10.0f),
				glm::vec3(10.0f, 10.0f, 10.0f),
				glm::vec3(-10.0f, -10.0f, 10.0f),
				glm::vec3(10.0f, -10.0f, 10.0f)
			};

			// Light Colors used for PBR
			glm::vec3 lightColors[] =
			{
				glm::vec3(20, 20, 20),
				glm::vec3(20, 20, 20),
				glm::vec3(20, 20, 20),
				glm::vec3(20, 20, 20)
			};


			// Sets uniform for light positions
			for (int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); i++)
			{
				m_Program->m_ShaderProgram->setUniform("lightPositions", lightPositions[i]);
			}

			// Sets uniform for light colors
			for (int i = 0; i < sizeof(lightColors) / sizeof(lightColors[0]); i++)
			{
				m_Program->m_ShaderProgram->setUniform("lightColors", lightColors[i]);
			}

			// Sets uniform for albedo, metallic, roughness and ao value
			m_Program->m_ShaderProgram->setUniform("albedo", glm::vec3(0, 0.5, 0));
			m_Program->m_ShaderProgram->setUniform("metallic", 0.0f);
			m_Program->m_ShaderProgram->setUniform("roughness", 0.1f);
			m_Program->m_ShaderProgram->setUniform("ao", 1.0f);

			// Sets uniform for camera position
			m_Program->m_ShaderProgram->setUniform("camPos", glm::vec3(10, 10, 0));

			m_Program->m_ShaderProgram->setUniform("u_Texture", m_Tex->m_TextureID);

			// Sets uniform for model matrix
			m_Program->m_ShaderProgram->setUniform("u_Model", getTransform()->getModel());


			// Draws model
			m_Program->m_ShaderProgram->draw(m_Mesh->m_Vao);
		}
	}
}