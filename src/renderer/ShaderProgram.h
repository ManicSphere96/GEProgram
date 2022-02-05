#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>

namespace renderer
{
	struct VertexArray;
	struct Sampler;
	struct Texture;

	struct ShaderProgram
	{
		public:
			ShaderProgram(std::string vert, std::string frag);
			~ShaderProgram();
			void draw(std::shared_ptr<VertexArray> vertexArray);
			void setUniform(std::string name, glm::mat4 uniform);
			void setUniform(std::string name, glm::vec3 uniform);
			void setUniform(std::string name, glm::vec4 uniform);
			void setUniform(std::string name, std::shared_ptr<Texture> texture);
			void setUniform(std::string name, float uniform);
			GLuint getId();
		private:
			GLuint id;
			std::vector<Sampler> samplers;
	};
}