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
			///returns object position
			glm::vec3 getPosition() { return m_position; }
			///returns object velocity
			glm::vec3 getVelocity() { return m_Velocity; }
			///returns object rotation
			glm::vec3 getRotation() { return m_rotation; }
			///returns bool value saying if the object is the player
			bool getIsPlayer() { return m_IsPlayer; }
			///returns bool value saying if the object can move
			bool getMovable() { return m_CanMove; }
			void move(float amount);
			void move(glm::vec3 amount);
			void rotate(float angle);
			void rotate(glm::vec3 angle);
			void setScale(glm::vec3 scale);
			void setFriction(float friction);
			void setVelocity(glm::vec3 vel);
			///sets bool value saying if the object is the player
			void setIsPlayer(bool isPlayer) { m_IsPlayer = isPlayer; };
			void gravityToggle();
			void movableToggle();
			void onTick();
		private:
			/// object position
			glm::vec3 m_position;
			/// object rotation
			glm::vec3 m_rotation;
			/// object scale
			glm::vec3 m_scale;
			/// object velocity
			glm::vec3 m_Velocity;
			/// object acceleration
			glm::vec3 m_Acceleration;
			/// objectfriction
			float m_Friction = 0.0f;
			/// object ability to move 
			bool m_CanMove;
			/// object ability to move under gravity
			bool m_Gravity;
			/// object gravity constant
			glm::vec3 m_GravityConst = glm::vec3 (0.0f,-10.0f,0.0f);
			/// object move amount if player
			float m_MoveAmount = 10.0f;
			/// object is or isn't player
			bool m_IsPlayer = false;
	};
}