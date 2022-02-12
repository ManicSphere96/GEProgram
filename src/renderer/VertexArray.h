#include <GL/glew.h>

#include <vector>
#include <memory>
#include <string>
#include "bugl2.h"

namespace renderer
{

	struct VertexBuffer;


	struct VertexArray
	 {
		public:
			VertexArray(std::string path);
			VertexArray();
			~VertexArray();
			void setBuffer(int location, std::shared_ptr<VertexBuffer> buffer);
			std::vector<struct bu::ConvexPlane> getPlanes() { return m_convexPlanes; };
			size_t getVertCount();
			GLuint getId();
		private:
			GLuint vaoId;
			GLuint positionsVbo = 0;
			GLuint tcsVbo = 0;
			GLuint normalsVbo = 0;
			std::vector<std::shared_ptr<VertexBuffer> > buffers;
			size_t vertCount;
			bool dirty;
			std::vector<struct bu::ConvexPlane> m_convexPlanes;

	};
}