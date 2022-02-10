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
	private:
		float m_Radius;
		
	};
}