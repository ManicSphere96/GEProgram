#include "SphereCollider.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"

namespace myengine
{
	void SphereCollider::onInit(float radius)
	{
		getCore()->registerCollider(getEntity()->getComponent<SphereCollider>());
		m_Radius = radius;
	}

	void SphereCollider::onDestroy()
	{
		getCore()->unregisterCollider(std::shared_ptr<SphereCollider>(this));
	}

	bool SphereCollider::isColliding(std::shared_ptr<SphereCollider> collider)
	{
		float distancebetween = glm::distance(collider->getTransform()->getPosition(),getTransform()->getPosition());
		if (distancebetween <= (m_Radius + collider->m_Radius))
		{

			return true;

		}
		else
		{
			return false;
		}
	}
	void SphereCollider::currentlyColliding(std::shared_ptr<SphereCollider> collidingObj)
	{
		
		glm::vec3 myVel = getTransform()->getVelocity();
		glm::vec3 itsVel = collidingObj->getTransform()->getVelocity();
		glm::vec3 myLoc = getTransform()->getPosition();
		glm::vec3 itsLoc = collidingObj->getTransform()->getPosition();
		glm::vec3 incedenceVector = (myLoc - itsLoc);
		incedenceVector = glm::normalize(incedenceVector);
		if ((this->getTransform()->getMovable()) && (collidingObj->getTransform()->getMovable()))
		{
			
			myVel += glm::length(itsVel) * incedenceVector;
			this->getTransform()->setVelocity(myVel);

			itsVel += glm::length(myVel) * -incedenceVector;
			collidingObj->getTransform()->setVelocity(itsVel);
		}
		else if ((this->getTransform()->getMovable()) && (!collidingObj->getTransform()->getMovable()))
		{
			
			
			this->getTransform()->setVelocity(this->getTransform()->getVelocity()- ( 2.0f * (glm::dot(this->getTransform()->getVelocity(), incedenceVector)*incedenceVector)));
		}
		else if ((!this->getTransform()->getMovable()) && (collidingObj->getTransform()->getMovable()))
		{
			collidingObj->getTransform()->setVelocity(collidingObj->getTransform()->getVelocity() - (2.0f * (glm::dot(collidingObj->getTransform()->getVelocity(), incedenceVector) * incedenceVector)));
		}


	}
}
