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
			GLuint id;
			glm::vec2 size;
	};
}