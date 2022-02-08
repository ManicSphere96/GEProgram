#pragma once
#include <memory>
#include <renderer.h>
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"
#include "TextureResource.h"

namespace myengine
{
	
	struct Texture;
	struct Test;

	struct MeshRenderer : Component
	{
		public:
			void setMesh(std::shared_ptr<Mesh> model) { m_Mesh = model; }
			void setTexture(std::shared_ptr<TextureResource> texture) { m_Tex = texture; }
			void setShader(std::shared_ptr<Shader> shaderProgram) { m_Program = shaderProgram; }
			void onDisplay();
		private:
			
			std::shared_ptr<Mesh> m_Mesh;
			std::shared_ptr<TextureResource> m_Tex;
			std::shared_ptr<Shader> m_Program;
	};
}