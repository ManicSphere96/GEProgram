#include "MeshRenderer.h"
#include "Model.h"
#include "Shader.h"
#include "Transform.h"


#include <renderer/renderer.h>

namespace myengine
{

	void MeshRenderer::onDisplay()
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
			program->shaderProgram->setUniform("lightPositions", lightPositions[i]);
		}

		// Sets uniform for light colors
		for (int i = 0; i < sizeof(lightColors) / sizeof(lightColors[0]); i++)
		{
			program->shaderProgram->setUniform("lightColors", lightColors[i]);
		}

		// Sets uniform for albedo, metallic, roughness and ao value
		program->shaderProgram->setUniform("albedo", glm::vec3(0, 0.5, 0));
		program->shaderProgram->setUniform("metallic", 0.0f);
		program->shaderProgram->setUniform("roughness", 0.1f);
		program->shaderProgram->setUniform("ao", 1.0f);

		// Sets uniform for camera position
		program->shaderProgram->setUniform("camPos", glm::vec3(10, 10, 0));

		

		// Sets uniform for model matrix
		program->shaderProgram->setUniform("u_Model", getTransform()->getModel());
		

		// Draws model
		program->shaderProgram->draw(mesh->vao);
	}
}