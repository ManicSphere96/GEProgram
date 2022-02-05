#include "Transform.h"

namespace myengine 
{
	Transform::Transform()
	{
		m_position = glm::vec3(0, 0, 0);
		m_rotation = glm::vec3(0, 0, 0);
		m_scale = glm::vec3(1, 1, 1);
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
}