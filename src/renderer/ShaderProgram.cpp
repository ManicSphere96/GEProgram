#include "ShaderProgram.h"
#include "VertexArray.h"
#include "Sampler.h"
#include "Texture.h"

#include <glm/ext.hpp>

namespace renderer
{
	ShaderProgram::ShaderProgram(std::string vert, std::string frag)
	{
		/**
		 * \brief Retrieves the vertex and fragment shader files.
		 * This will then setup them up along with any attributes
		 * and uniforms which need to be set
		 */

		std::ifstream vertFile(vert);
		std::string vShaderText;

		if (!vertFile.is_open())
		{
			std::cout << "Cannot open vertex shader file" << std::endl;
			throw std::exception();
		}
			std::string temp;

		while (std::getline(vertFile, temp))
		{
			vShaderText += temp;
			vShaderText.push_back('\n');
		}

		vertFile.close();

		std::ifstream fragFile(frag);
		std::string fShaderText;

		if (!fragFile.is_open())
		{
			std::cout << "Cannot open fragment shader file" << std::endl;
			throw std::exception();
		}

		while (std::getline(fragFile, temp))
		{
			fShaderText += temp;
			fShaderText.push_back('\n');
		}

		fragFile.close();

		const GLchar* vertShaderSrc = vShaderText.c_str();

		const GLchar* fragShaderSrc = fShaderText.c_str();

		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &vertShaderSrc, NULL);
		glCompileShader(vertexShaderId);
		GLint success = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(vertexShaderId, maxLength, &maxLength, &errorLog.at(0));
			std::cout << &errorLog.at(0) << std::endl;
			throw std::exception();
		}

		GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShaderId, 1, &fragShaderSrc, NULL);
		glCompileShader(fragShaderId);
		glGetShaderiv(fragShaderId, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragShaderId, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(fragShaderId, maxLength, &maxLength, &errorLog.at(0));
			std::cout << &errorLog.at(0) << std::endl;
			throw std::exception();
		}

		id = glCreateProgram();
		glAttachShader(id, vertexShaderId);
		glAttachShader(id, fragShaderId);

		glBindAttribLocation(id, 0, "in_Position");
		glBindAttribLocation(id, 1, "in_Texcoord");

		glLinkProgram(id);
		glGetProgramiv(id, GL_LINK_STATUS, &success);

		if (!success)
		{
			throw std::exception();
		}

		glDetachShader(id, vertexShaderId);
		glDeleteShader(vertexShaderId);
		glDetachShader(id, fragShaderId);
		glDeleteShader(fragShaderId);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 100.0f);

		glm::mat4 view(1.0f);
		view = glm::translate(view, glm::vec3(0.0f,0.0f,-1.5f));

		glm::mat4 view2(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));

		setUniform("u_Projection", projection);
		setUniform("u_View", view);
		setUniform("projMat", projection);
		setUniform("viewMat", view2);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(id);
	}

	void ShaderProgram::draw(std::shared_ptr<VertexArray> vertexArray)
	{
		/// Draws the model/triangle

		glUseProgram(id);
		glBindVertexArray(vertexArray->getId());

		for (size_t i = 0; i < samplers.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			if (samplers.at(i).texture)
			{
				glBindTexture(GL_TEXTURE_2D, samplers.at(i).texture->getId());
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		glDrawArrays(GL_TRIANGLES, 0, vertexArray->getVertCount());

		for (size_t i = 0; i < samplers.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glBindVertexArray(0);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string name, glm::mat4 uniform)
	{
		/// Sets the uniform value with the name provided by the string

		glUseProgram(id);
		GLint loc = glGetUniformLocation(id, name.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(uniform));
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string name, glm::vec3 uniform)
	{
		/// Sets the uniform value with the name provided by the string

		glUseProgram(id);
		GLint loc = glGetUniformLocation(id, name.c_str());
		glUniform3f(loc, uniform.x, uniform.y, uniform.z);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string name, glm::vec4 uniform)
	{
		/// Sets the uniform value with the name provided by the string

		glUseProgram(id);
		GLint loc = glGetUniformLocation(id, name.c_str());
		glUniform4f(loc, uniform.x, uniform.y, uniform.z, uniform.w);
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string name, std::shared_ptr<Texture> texture)
	{
		/// Sets the uniform for the texture with the name provided by the string

		glUseProgram(id);
		glUniform1i(glGetUniformLocation(id, name.c_str()), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getId());
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(std::string name, float uniform)
	{
		/// Sets the uniform float value with the name provided by the string

		glUseProgram(id);
		GLint loc = glGetUniformLocation(id, name.c_str());
		glUniform1f(loc, uniform);
		glUseProgram(0);
	}

	GLuint ShaderProgram::getId()
	{
		/// Returns the id

		return id;
	}
}