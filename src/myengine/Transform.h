#pragma once

#include "Component.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace myengine
{
	struct Transform : Component
	{
		public:
			Transform();
			glm::mat4 getModel();
			void setPosition(glm::vec3 pos);
			glm::vec3 getPosition() { return m_position; }
			void move(float amount);
			void move(glm::vec3 amount);
			void rotate(float angle);
			void rotate(glm::vec3 angle);
			void setScale(glm::vec3 scale);
		private:
			glm::vec3 m_position;
			glm::vec3 m_rotation;
			glm::vec3 m_scale;
	};
}