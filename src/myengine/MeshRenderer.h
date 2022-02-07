#pragma once
#include <memory>
#include <renderer.h>
#include "Component.h"

namespace myengine
{
	struct Model;
	struct Texture;
	struct Test;

	struct MeshRenderer : Component
	{
		public:
			void setMesh(std::shared_ptr<Model> model) { mesh = model; }
			void setTexture(std::shared_ptr<renderer::Texture> texture) { tex = texture; }
			void setShader(std::shared_ptr<renderer::ShaderProgram > shaderProgram) { program = shaderProgram; }
			void onDisplay();
		private:
			
			std::shared_ptr<Model> mesh;
			std::shared_ptr<renderer::Texture> tex;
			std::shared_ptr<renderer::ShaderProgram > program;
	};
}