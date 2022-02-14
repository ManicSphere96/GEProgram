#pragma once
#include <memory>
#include <renderer.h>
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"
#include "TextureResource.h"

namespace myengine
{

	struct MeshRenderer : Component
	{
		public:
			/// sets the mesh up for use
			void setMesh(std::shared_ptr<Mesh> model) { m_Mesh = model; }
			/// sets the texture up for use
			void setTexture(std::shared_ptr<TextureResource> texture) { m_Tex = texture; }
			/// sets the shader program up for use
			void setShader(std::shared_ptr<Shader> shaderProgram) { m_Program = shaderProgram; }
			/// Returns the visibility of the object
			bool getVisible() { return m_IsVisible; }
			/// Returns the mesh
			std::shared_ptr<Mesh> getMesh() { return m_Mesh; }
			void setVisible(bool);
			
		private:
			void onDisplay();
			///Holds the Mesh
			std::shared_ptr<Mesh> m_Mesh;
			///Holds the Texture
			std::shared_ptr<TextureResource> m_Tex;
			///Holds the shader Program
			std::shared_ptr<Shader> m_Program;
			///if the object id visible this is true
			bool m_IsVisible = true;
	};
}