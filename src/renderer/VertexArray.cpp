#include "VertexArray.h"
#include "VertexBuffer.h"

#include "bugl2.h"

namespace renderer
{
	VertexArray::VertexArray(std::string path)
	{
		/// Sets up the vertex array with a path to the model

		vertCount = buLoadModel(path, &positionsVbo, &tcsVbo, &normalsVbo);

		glGenVertexArrays(1, &vaoId);
		if (!vaoId) throw std::exception();
		glBindVertexArray(vaoId);

		glBindBuffer(GL_ARRAY_BUFFER, positionsVbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, tcsVbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, normalsVbo);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		dirty = false;
	}

	VertexArray::VertexArray()
	{
		/// Sets up the vertex array for the triangle

		glGenVertexArrays(1, &vaoId);
		vertCount = 0;

		if (!vaoId)
		{
			throw std::exception();
		}

		dirty = true;
		buffers.resize(20);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &vaoId);
		glDeleteBuffers(1, &positionsVbo);
		glDeleteBuffers(1, &tcsVbo);
		glDeleteBuffers(1, &normalsVbo);
	}

	void VertexArray::setBuffer(int location, std::shared_ptr<VertexBuffer> buffer)
	{
		/// Sets the buffer count

		buffers.at(location) = buffer;

		if (location == 0)
		{
			vertCount = buffer->getSize();
		}

		dirty = true;
	}

	size_t VertexArray::getVertCount()
	{
		/// Returns the vert count

		return vertCount;
	}

	GLuint VertexArray::getId()
	{
		/**
		 * \brief Sets up the vertex array
		 * and returns the id
		 */

		if (dirty)
		{
			glBindVertexArray(vaoId);

			for (size_t i = 0; i < buffers.size(); i++)
			{
				if (!buffers.at(i))
					continue;

				glBindBuffer(GL_ARRAY_BUFFER, buffers.at(i)->getId());

				glVertexAttribPointer(i, buffers.at(i)->getComponents(), GL_FLOAT, GL_FALSE,
					0, (void*)0);

				glEnableVertexAttribArray(i);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			glBindVertexArray(0);
			dirty = false;
		}

		return vaoId;
	}
}