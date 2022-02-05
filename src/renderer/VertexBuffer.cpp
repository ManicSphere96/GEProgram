#include "VertexBuffer.h"

namespace renderer
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &id);

		if (!id)
		{
			throw std::exception();
		}

		components = 0;
		dirty = true;
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void VertexBuffer::add(glm::vec2 value)
	{
		/// Adds a glm::vec2 value to the vertex buffer

		data.push_back(value.x);
		data.push_back(value.y);

		components = 2;
		dirty = true;
	}

	void VertexBuffer::add(glm::vec3 value)
	{
		/// Adds a glm::vec3 value to the vertex buffer

		data.push_back(value.x);
		data.push_back(value.y);
		data.push_back(value.z);

		components = 3;
		dirty = true;
	}

	void VertexBuffer::add(glm::vec4 value)
	{
		/// Adds a glm::vec4 value to the vertex buffer

		data.push_back(value.x);
		data.push_back(value.y);
		data.push_back(value.z);
		data.push_back(value.w);

		components = 4;
		dirty = true;
	}

	int VertexBuffer::getComponents()
	{
		/// Returns the components

		return components;
	}

	size_t VertexBuffer::getSize()
	{
		/// Returns the components

		return data.size();
	}

	GLuint VertexBuffer::getId()
	{
		/**
		 * Sets up the vertex buffer and
		 * returns the id
		 */

		if (dirty)
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);

			glBufferData(GL_ARRAY_BUFFER,  sizeof(data.at(0)) * data.size(), &data.at(0), GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			dirty = false;
		}

		return id;
	}
}