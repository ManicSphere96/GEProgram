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
			std::vector<struct bu::ConvexPlane> getPlanes() { return m_ConvexPlanes; };
			size_t getVertCount();
			GLuint getId();
		private:
			GLuint m_VaoId;
			GLuint m_PositionsVbo = 0;
			GLuint m_TcsVbo = 0;
			GLuint m_NormalsVbo = 0;
			std::vector<std::shared_ptr<VertexBuffer> > m_Buffers;
			size_t m_VertCount;
			bool m_Dirty;
			std::vector<struct bu::ConvexPlane> m_ConvexPlanes;

	};
}