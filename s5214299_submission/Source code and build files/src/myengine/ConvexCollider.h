#pragma once
#include <renderer.h>
#include "Component.h"
#include "SphereCollider.h"

namespace myengine
{
	struct ConvexCollider : Component
	{
	public:
		void onInit(std::shared_ptr<renderer::VertexArray> vao);
		void onDestroy();
		bool isColliding(std::shared_ptr<SphereCollider> collider);
		///Returns the hitcount 
		int getHitCount() { return m_HitCount; }
		///Returns the incedent of the collision
		glm::vec3 getIncident() { return m_Incident; }
		///Sets the incedent of the collision
		void setIncident(glm::vec3 incident) { m_Incident = incident; }
	private:
		///Holds the VAO from the mesh
		std::shared_ptr<renderer::VertexArray> m_Vao;
		///Holds the hitcount
		int m_HitCount = 0;
		///Holds the incident from the collision
		glm::vec3 m_Incident;
	};
}