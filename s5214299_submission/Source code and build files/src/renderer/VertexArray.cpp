#include "VertexArray.h"
#include "VertexBuffer.h"

#pragma warning(disable: 4101) //Unused variable for execption 'e' in bugl2.h
#pragma warning(disable: 26451) // 4 byte to 8 byte cast. Check build target 32 vs 64


namespace renderer
{
	VertexArray::VertexArray(std::string path)
	{
		/// Sets up the vertex array object with a path to the model and sets up my positions and normals buffers.

		m_VertCount = buLoadModel(path, &m_PositionsVbo, &m_TcsVbo, &m_NormalsVbo, &m_ConvexPlanes);

		glGenVertexArrays(1, &m_VaoId);
		if (!m_VaoId) throw std::exception();
		glBindVertexArray(m_VaoId);

		glBindBuffer(GL_ARRAY_BUFFER, m_PositionsVbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_TcsVbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, m_NormalsVbo);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_Dirty = false;
	}

	VertexArray::VertexArray()
	{
		/// Sets up the vertex array for the triangle

		glGenVertexArrays(1, &m_VaoId);
		m_VertCount = 0;

		if (!m_VaoId)
		{
			throw std::exception();
		}

		m_Dirty = true;
		m_Buffers.resize(20);
	}

	VertexArray::~VertexArray()
	{
		
		/// Deletes buffers when destructing.
		
		glDeleteVertexArrays(1, &m_VaoId);
		glDeleteBuffers(1, &m_PositionsVbo);
		glDeleteBuffers(1, &m_TcsVbo);
		glDeleteBuffers(1, &m_NormalsVbo);
	}

	void VertexArray::setBuffer(int location, std::shared_ptr<VertexBuffer> buffer)
	{
		/// Sets the buffer count

		m_Buffers.at(location) = buffer;

		if (location == 0)
		{
			m_VertCount = buffer->getSize();
		}

		m_Dirty = true;
	}

	size_t VertexArray::getVertCount()
	{
		/// Returns the vert count

		return m_VertCount;
	}

	GLuint VertexArray::getId()
	{
		
		 ///brief Sets up the vertex array and returns the id
		

		if (m_Dirty)
		{
			glBindVertexArray(m_VaoId);

			for (size_t i = 0; i < m_Buffers.size(); i++)
			{
				if (!m_Buffers.at(i))
					continue;

				glBindBuffer(GL_ARRAY_BUFFER, m_Buffers.at(i)->getId());

				glVertexAttribPointer((GLuint)i, m_Buffers.at(i)->getComponents(), GL_FLOAT, GL_FALSE,
					0, (void*)0);

				glEnableVertexAttribArray((GLuint)i);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			glBindVertexArray(0);
			m_Dirty = false;
		}

		return m_VaoId;
	}
}