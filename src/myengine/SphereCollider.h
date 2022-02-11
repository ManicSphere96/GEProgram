#pragma once
#include "Component.h"
#include "Core.h"

namespace myengine
{
	struct SphereCollider : Component
	{
	public:
		void onInit(float radius);
		void onDestroy();
		bool isColliding(std::shared_ptr<SphereCollider> _collider);
		void currentlyColliding(std::shared_ptr<SphereCollider> collidingObj);
		void setRadius(float rad);
		int getHitCount() { return m_HitCount; }
		~SphereCollider();
	private:
		float m_Radius;
		int m_HitCount = 0;
		
	};
}