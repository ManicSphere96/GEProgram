#include "Texture.h"

#pragma warning(disable: 26451) // 4 byte to 8 byte cast. Check build target 32 vs 64
#pragma warning(disable: 6011) // Deference NULL 
#pragma warning(disable: 6308) // realloc check. 
#pragma warning(disable: 28182) // Deference NULL. 

// TODO increase stack size to alllow ofr stb_image.h as it needs 64k of stack.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace renderer
{
	Texture::Texture(std::string path)
	{
		/// Sets up the texture which will be used for the model

		int w = 0;
		int h = 0;

		glGenTextures(1, &id);

		if (!id)
		{
			throw std::exception();
		}

		unsigned char* data = stbi_load(path.c_str(), &w, &h, NULL, 4);

		glBindTexture(GL_TEXTURE_2D, id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data);

		free(data);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glm::vec2 Texture::getSize()
	{
		/// Returns the size of the model

		return size;
	}

	GLuint Texture::getId()
	{
		/// Returns the id of the texture

		return id;
	}
}

