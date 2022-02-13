#include <GL/glew.h>
#include <glm/glm.hpp>

namespace renderer
{
	struct Texture;

	struct Sampler
	{
		public:
			/// The id which is used for the sampler
			GLint m_Id;
			/// The texture used for the sampler
			Texture* m_Texture;
	};
}