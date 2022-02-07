#include "MeshRenderer.h"
#include "Model.h"
#include "Shader.h"
#include "Transform.h"


#include <renderer.h>

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
			program->setUniform("lightPositions", lightPositions[i]);
		}

		// Sets uniform for light colors
		for (int i = 0; i < sizeof(lightColors) / sizeof(lightColors[0]); i++)
		{
			program->setUniform("lightColors", lightColors[i]);
		}

		// Sets uniform for albedo, metallic, roughness and ao value
		program->setUniform("albedo", glm::vec3(0, 0.5, 0));
		program->setUniform("metallic", 0.0f);
		program->setUniform("roughness", 0.1f);
		program->setUniform("ao", 1.0f);

		// Sets uniform for camera position
		program->setUniform("camPos", glm::vec3(10, 10, 0));

		

		// Sets uniform for model matrix
		program->setUniform("u_Model", getTransform()->getModel());
		

		// Draws model
		program->draw(mesh->vao);
	}
}