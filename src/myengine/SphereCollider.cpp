#include "SphereCollider.h"
#include "Core.h"
#include "Entity.h"

namespace myengine
{
	void SphereCollider::onInitialize()
	{
		getCore()->registerCollider(
			getEntity()->getComponent<SphereCollider>());
		m_radius = 2;
	}

	void SphereCollider::onDestroy()
	{
		getCore()->unregisterCollider(this);
	}

	bool SphereCollider::isColliding(std::shared_ptr<SphereCollider> collider)
	{
		//Find distance between given collider and this collider
		float distance = std::distance(collider->getTransform()->m_position   , getTransform()->m_position);
		//Add both radii together and compare to the distance if distance 
		//is equal or smaller then they are colliding
		float addedRadius = m_radius + collider->getRadius();
		if (distance <= addedRadius)
		{
			return true;
		}
		return false;
	}
	
}