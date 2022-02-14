#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>

namespace renderer
{
	struct Texture
	{
		public:
			Texture(std::string path);
			glm::vec2 getSize();
			GLuint getId();
		private:
			/// Texture ID.
			GLuint m_Id;
			///Size of texture.
			glm::vec2 m_Size = { 0, 0 };
	};
}