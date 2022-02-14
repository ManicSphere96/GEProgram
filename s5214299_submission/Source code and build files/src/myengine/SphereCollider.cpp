
#include <renderer.h>
#include "SphereCollider.h"

// This should not have to be added, but without it the compiler says:
// Error	C2027	use of undefined type 'myengine::Core'	myengine	
#include "Core.h" 

#include "Component.h"
#include "Transform.h"


namespace myengine
{
	void SphereCollider::onInit(float radius)
	{
		///Registers Collider in the Vector in Core 
		getCore()->registerCollider(getEntity()->getComponent<SphereCollider>());
		m_Radius = radius;
	}

	void SphereCollider::onDestroy()
	{
		///Unregisters Collider in the Vector in Core
		getCore()->unregisterCollider(this);
	}

	bool SphereCollider::isColliding(std::shared_ptr<SphereCollider> collider)
	{
		//Tests for collisipon between this collider and the given collider
		float distancebetween = glm::distance(collider->getTransform()->getPosition(),getTransform()->getPosition());
		if (distancebetween <= (m_Radius + collider->m_Radius))
		{
			this->m_HitCount++;
			collider->m_HitCount++;
			m_CollidedName = collider->getEntity()->getName();
			collider->setCollidedName(getEntity()->getName());
			return true;
		}
		else
		{ 
			return false;
		}
	}
	void SphereCollider::currentlyColliding(std::shared_ptr<SphereCollider> collidingObj)
	{
		/// this is what affects the colliding objects velocity based on the collision.
		glm::vec3 myVel = getTransform()->getVelocity();
		glm::vec3 itsVel = collidingObj->getTransform()->getVelocity();
		glm::vec3 myLoc = getTransform()->getPosition();
		glm::vec3 itsLoc = collidingObj->getTransform()->getPosition();
		/// setting up the incedence vector and normalizing it.
		glm::vec3 incedenceVector = (myLoc - itsLoc);
		incedenceVector = glm::normalize(incedenceVector);
		if ((this->getTransform()->getMovable()) && (collidingObj->getTransform()->getMovable()))
		{
			///if both objects can move do this
			myVel += glm::length(itsVel) * incedenceVector;
			this->getTransform()->setVelocity(myVel);

			itsVel += glm::length(myVel) * -incedenceVector;
			collidingObj->getTransform()->setVelocity(itsVel);
		}
		else if ((this->getTransform()->getMovable()) && (!collidingObj->getTransform()->getMovable()))
		{	
			///if this collider can move but the other cant do this
			float incedenceVelScalar = glm::dot(myVel, incedenceVector);
			if (incedenceVelScalar < -GAMMA)
			{
				m_HasCollided = true;
			}
			getTransform()->setPosition(itsLoc + incedenceVector * (m_Radius + collidingObj->getRadius()));

			if (incedenceVelScalar > -EPSILON)
			{
				getTransform()->setVelocity(myVel - (-incedenceVector * incedenceVelScalar));
				m_HasCollided = false;
			}
			this->getTransform()->setVelocity(this->getTransform()->getVelocity() - ( 2.0f * (glm::dot(this->getTransform()->getVelocity(), incedenceVector)*incedenceVector)));
		}
		else if ((!this->getTransform()->getMovable()) && (collidingObj->getTransform()->getMovable()))
		{
			///if this collider cant move but the other can do this
			float incedenceVelScalar = glm::dot(itsVel, -incedenceVector);
			if (incedenceVelScalar < -GAMMA)
			{
				m_HasCollided = true;
			}
			collidingObj->getTransform()->setPosition(myLoc + -incedenceVector * (m_Radius + collidingObj->getRadius()));
			if (incedenceVelScalar > -EPSILON)
			{
				collidingObj->getTransform()->setVelocity(itsVel - (-incedenceVector * incedenceVelScalar));
				m_HasCollided = false;
				
			}

			collidingObj->getTransform()->setVelocity(collidingObj->getTransform()->getVelocity() - (2.0f * (glm::dot(collidingObj->getTransform()->getVelocity(), -incedenceVector) * -incedenceVector)));
		}


	}
	void SphereCollider::toggleCanDie()
	{
		///changes the bool value m_CanDie
		if (!m_CanDie)
		{
			m_CanDie = true;
		}
		else
		{
			m_CanDie = false;
		}
	}
	void SphereCollider::toggleHasCollided()
	{
		///changes the bool value m_HasCollided
		if (!m_HasCollided)
		{
			m_HasCollided = true;
		}
		else
		{
			m_HasCollided = false;
		}
	}
}

