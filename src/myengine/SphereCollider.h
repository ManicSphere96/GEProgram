#pragma once
#include "Component.h"

namespace myengine
{
	struct SphereCollider : Component
	{
	public:
		void onInit(float radius);
		void onDestroy();
		bool isColliding(std::shared_ptr<SphereCollider> _collider);
		void currentlyColliding(std::shared_ptr<SphereCollider> collidingObj);
		int getHitCount() { return m_HitCount; }
		int getHasCollided() { return m_HasCollided; }
		float getRadius() { return m_Radius; }
		bool getCanDie() { return m_CanDie; }
		void toggleCanDie();
		void toggleHasCollided();
	private:
		float m_Radius = 0.0f;
		int m_HitCount = 0;
		bool m_HasCollided = false;
		bool m_CanDie = true;
		
	};
}