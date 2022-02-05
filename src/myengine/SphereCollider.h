#pragma once
#include "Component.h"

namespace myengine
{
	struct Core;
	struct Entity;

	struct SphereCollider : Component
	{
		public:
			void onInitialize();
			void onDestroy();
			bool isColliding(std::shared_ptr<SphereCollider> _collider);
			void setRadius(float radius) { m_radius = radius; }
			float getRadius() { return m_radius; }
		private:
			float m_radius;
	};
}