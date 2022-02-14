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
		/// Returns how many times object has been hit
		int getHitCount() { return m_HitCount; }
		/// Returns if the object has collided this tick
		int getHasCollided() { return m_HasCollided; }
		/// Returns radius of collider
		float getRadius() { return m_Radius; }
		/// Returns if the object can die
		bool getCanDie() { return m_CanDie; }
		void toggleCanDie();
		void toggleHasCollided();
		/// Sets if it has been colided with
		void setHasCollided(bool hascollided) { m_HasCollided = hascollided; }
		/// Sets the object it collided with name
		void setCollidedName(std::string name) { m_CollidedName = name; }
		/// Returns if the object has collided the name of the collider
		std::string getCollidedName() { return m_CollidedName; }

	private:
		/// when an object collides with this collider this gets set to its name
		std::string m_CollidedName = "";
		/// collider radius
		float m_Radius = 0.0f;
		/// collider hit count
		int m_HitCount = 0;
		/// if collider has been hit this tick
		bool m_HasCollided = false;
		// if the collider and the object can die
		bool m_CanDie = true;
		
	};
}