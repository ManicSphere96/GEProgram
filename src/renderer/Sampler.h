#include <GL/glew.h>
#include <glm/glm.hpp>

namespace renderer
{
	struct Texture;

	struct Sampler
	{
		public:
			/// The id which is used for the sampler
			GLint id;
			/// The texture used for the sampler
			Texture* texture;
	};
}