#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Component.h"


namespace myengine
{
	
	struct Transform : Component
	{
		public:
			Transform();
			glm::mat4 getModel();
			void setPosition(glm::vec3 pos);
			void setAcceleration(glm::vec3 acceleration);
			glm::vec3 getPosition() { return m_position; }
			glm::vec3 getVelocity() { return m_Velocity; }
			glm::vec3 getRotation() { return m_rotation; }
			bool getIsPlayer() { return m_IsPlayer; }
			bool getMovable() { return m_CanMove; }
			void move(float amount);
			void move(glm::vec3 amount);
			void rotate(float angle);
			void rotate(glm::vec3 angle);
			void setScale(glm::vec3 scale);
			void setFriction(float friction);
			void setVelocity(glm::vec3 vel);
			void SetIsPlayer(bool isPlayer) { m_IsPlayer = isPlayer; };
			void gravityToggle();
			void movableToggle();
			void onTick();
		private:
			glm::vec3 m_position;
			glm::vec3 m_rotation;
			glm::vec3 m_scale;
			glm::vec3 m_Velocity;
			glm::vec3 m_Acceleration;
			float m_Friction = 0.0f;
			bool m_CanMove;
			bool m_Gravity;
			glm::vec3 m_GravityConst = glm::vec3 (0.0f,-10.0f,0.0f);
			glm::vec3 m_RotationConst = glm::vec3(1.0f, 2.0f, .0f);
			float m_MoveAmount = 1.0f;
			bool m_IsPlayer = false;
	};
}