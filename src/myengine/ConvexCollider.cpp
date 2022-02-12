#include <renderer.h>
#include "ConvexCollider.h"

// This should not have to be added, but without it the compiler says:
// Error	C2027	use of undefined type 'myengine::Core'	myengine	
#include "Core.h"

#include "Component.h"
#include "Transform.h"

namespace myengine
{
	void ConvexCollider::onInit(std::shared_ptr<renderer::VertexArray> vao)
	{
		getCore()->registerConvexCollider(getEntity()->getComponent<ConvexCollider>());
		m_Vao = vao;
	}
	void ConvexCollider::onDestroy()
	{
		getCore()->unregisterConvexCollider(this);
	}

	

	bool ConvexCollider::isColliding(std::shared_ptr<SphereCollider> collider)
	{
		/*
		float distancebetween = glm::distance(collider->getTransform()->getPosition(), getTransform()->getPosition());
		if (distancebetween <= (m_Radius + ))
		{
			this->m_HitCount++;
			collider->m_HitCount++;
			return true;

		}
		else
		{
			return false;
		}
		*/
		bool isInside = true;
		for (int pi = 0; pi < (int)m_Vao->getPlanes().size(); pi++)
		{
			// std::vector<struct bu::ConvexPlane> getPlanes() { return m_convexPlanes; };
			// distance is the projection of the line from sphere center to point on plane onto the normal
			float distance = glm::dot((collider->getTransform()->getPosition() - m_Vao->getPlanes()[pi].point), m_Vao->getPlanes()[pi].normal);
			if (distance > collider->getRadius())
			{
				isInside = false;
				break;
			}
			else
			{
				if (distance > 0.0)
				{
					// incident vector will be the normal pointing the other way "-n"
					SetIncident(-m_Vao->getPlanes()[pi].normal);
				}
			}
		}
		return false;
	}
	void ConvexCollider::currentlyColliding(std::shared_ptr<SphereCollider> collidingObj)
	{
		glm::vec3 itsVel = collidingObj->getTransform()->getVelocity();
		collidingObj->getTransform()->setVelocity(itsVel - (2.0f * (glm::dot(itsVel, m_Incident) * m_Incident)));
	}
	
}


