#define PI 3.1415925

#include "Transform.h"
#include "Keyboard.h"
#include "Component.h"
#include "Core.h"

namespace myengine 
{
	Transform::Transform()
	{
		m_position = glm::vec3(0, 0, 0);
		m_rotation = glm::vec3(0, 0, 0);
		m_scale = glm::vec3(1, 1, 1);
		m_Acceleration = glm::vec3(0, 0, 0);
		m_Velocity = glm::vec3(0, 0, 0);
		m_CanMove = true;
		m_Gravity = true;

	}

	glm::mat4 Transform::getModel()
	{
		/// Returns the model identity matrix

		glm::mat4 model(1.0f);
		model = glm::translate(model, m_position);
		model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
		

		return model;
	}

	void Transform::setPosition(glm::vec3 pos)
	{
		/// Sets the position for the model/triangle

		m_position = pos;
	}

	void Transform::setAcceleration(glm::vec3 acceleration)
	{
		if (m_CanMove)
		{
			m_Acceleration += acceleration;
		}
		else
		{
			m_Acceleration = glm::vec3(0, 0, 0);
		}
		 
	}

	void Transform::setFriction(float friction)
	{
		m_Friction = friction;
	}

	void Transform::move(float amount)
	{
		/// Moves the position of the model/triangle using a float value

		glm::mat4 model(1.0f);
		model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
		glm::vec3 fwd = glm::vec3(model * glm::vec4(0,0,1,1));
		m_position += fwd * amount;
	}

	void Transform::move(glm::vec3 amount)
	{
		/// Moves the position of the model/triangle using a glm::vec3 value

		glm::mat4 model(1.0f);
		model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
		glm::vec3 fwd = glm::vec3(model * glm::vec4(amount, 1));
		m_position += fwd;
	}


	void Transform::rotate(float angle)
	{
		/// Sets the rotation for the model/triangle using a float value

		m_rotation.y += angle;
	}

	void Transform::rotate(glm::vec3 angle)
	{
		/// Sets the rotation for the model/triangle using a glm::vec3 value

		m_rotation += angle;
	}
	void Transform::setScale(glm::vec3 scale)
	{
		scale = m_scale;
	}

	void Transform::onTick()
	{
		if (m_IsPlayer)
		{
			for (int i = 0; i < (int)getKeyboard()->keys.size(); i++)
			{
				// If the player presses space it will set yMomentum to 1.25
				if ((getKeyboard()->keys[i] == SDLK_UP))
				{
					getTransform()->setAcceleration(glm::vec3(0, m_MoveAmount, 0));
				}
				else if ((getKeyboard()->keys[i] == SDLK_DOWN))
				{
					getTransform()->setAcceleration(glm::vec3(0, -m_MoveAmount, 0));
				}
				// This will then make the player jump
				else if ((getKeyboard()->keys[i] == SDLK_LEFT))
				{
					getTransform()->setAcceleration(glm::vec3(-m_MoveAmount, 0, 0));
				}
				else if ((getKeyboard()->keys[i] == SDLK_RIGHT))
				{
					getTransform()->setAcceleration(glm::vec3(m_MoveAmount, 0, 0));
				}
				else if ((getKeyboard()->keys[i] == SDLK_s))
				{
					getTransform()->setAcceleration(glm::vec3(0, 0, -m_MoveAmount));
				}
				else if ((getKeyboard()->keys[i] == SDLK_w))
				{
					getTransform()->setAcceleration(glm::vec3(0, 0, m_MoveAmount));
				}
			}
		}
		if (m_CanMove)
		{
			m_Velocity = m_Velocity + (-m_Velocity * m_Friction);
			glm::vec3 deltaPos = m_Velocity * getCore()->getEnvironment()->getDeltaTime();
			if (getCore()->getEnvironment()->getDeltaTime() == 0)
			{
				m_position = m_position + m_Velocity;
			}
			else
			{
				m_Velocity = m_Velocity + (m_Acceleration * getCore()->getEnvironment()->getDeltaTime());
				if (m_Gravity)
				{
					m_Velocity = m_Velocity + (m_GravityConst * getCore()->getEnvironment()->getDeltaTime());
				}
				
				m_position = m_position + m_Velocity * getCore()->getEnvironment()->getDeltaTime();
			}
			if (m_Velocity != glm::vec3(0, 0, 0))
			{
				glm::vec3 normalDPos = glm::normalize(deltaPos);
				m_rotation = m_rotation + glm::vec3(
					(-asinf(deltaPos.y / getComponent<SphereCollider>()->getRadius()) * 180.0f / PI),
					(asinf(deltaPos.x / getComponent<SphereCollider>()->getRadius()) * 180.0f / PI),
					(asinf(deltaPos.z / getComponent<SphereCollider>()->getRadius()) * 180.0f / PI));
			}
		}
		m_Acceleration = glm::vec3(0, 0, 0);
	}
	void Transform::setVelocity(glm::vec3 vel)
	{
		if (m_CanMove) 
		{
			m_Velocity = vel;
		}
		else
		{
			m_Velocity = glm::vec3(0, 0, 0);
		}
		
	}
	void Transform::gravityToggle()
	{
		if (m_Gravity)
		{
			m_Gravity = false;
		}
		else
			m_Gravity = true;
	}
	void Transform::movableToggle()
	{
		if (m_CanMove)
		{
			m_CanMove = false;
		}
		else
			m_CanMove = true;
	}
	
}