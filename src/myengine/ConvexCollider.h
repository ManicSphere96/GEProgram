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
		int getHitCount() { return m_HitCount; }
		glm::vec3 getIncident() { return m_Incident; }
		void setIncident(glm::vec3 incident) { m_Incident = incident; }
	private:
		std::shared_ptr<renderer::VertexArray> m_Vao;
		float m_Radius = 0.0f;
		int m_HitCount = 0;
		glm::vec3 m_Incident;
	};
}