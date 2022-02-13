#include "VertexBuffer.h"

namespace renderer
{
	VertexBuffer::VertexBuffer()
	{
		/// <summary>
		/// Generates A Vertex Buffer Objectand returns the ID
		/// </summary>
		glGenBuffers(1, &m_Id);

		if (!m_Id)
		{
			throw std::exception();
		}

		m_Components = 0;
		m_Dirty = true;
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_Id);
	}

	void VertexBuffer::add(glm::vec2 value)
	{
		/// Adds a glm::vec2 value to the vertex buffer

		m_Data.push_back(value.x);
		m_Data.push_back(value.y);

		m_Components = 2;
		m_Dirty = true;
	}

	void VertexBuffer::add(glm::vec3 value)
	{
		/// Adds a glm::vec3 value to the vertex buffer

		m_Data.push_back(value.x);
		m_Data.push_back(value.y);
		m_Data.push_back(value.z);

		m_Components = 3;
		m_Dirty = true;
	}

	void VertexBuffer::add(glm::vec4 value)
	{
		/// Adds a glm::vec4 value to the vertex buffer

		m_Data.push_back(value.x);
		m_Data.push_back(value.y);
		m_Data.push_back(value.z);
		m_Data.push_back(value.w);

		m_Components = 4;
		m_Dirty = true;
	}

	int VertexBuffer::getComponents()
	{
		/// Returns the components

		return m_Components;
	}

	size_t VertexBuffer::getSize()
	{
		/// Returns the components

		return m_Data.size();
	}

	GLuint VertexBuffer::getId()
	{
		/**
		 * Sets up the vertex buffer and
		 * returns the id
		 */

		if (m_Dirty)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_Id);

			glBufferData(GL_ARRAY_BUFFER,  sizeof(m_Data.at(0)) * m_Data.size(), &m_Data.at(0), GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			m_Dirty = false;
		}

		return m_Id;
	}
}