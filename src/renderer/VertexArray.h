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
			/// extracts the Vector for use in convex collider.
			std::vector<struct bu::ConvexPlane> getPlanes() { return m_ConvexPlanes; };
			size_t getVertCount();
			GLuint getId();
		private:
			/// Vertex array object ID.
			GLuint m_VaoId;
			///Vertex Buffer Object info.
			GLuint m_PositionsVbo = 0;
			///Vertex Buffer Object info.
			GLuint m_TcsVbo = 0;
			///Vertex Buffer Object info.
			GLuint m_NormalsVbo = 0;
			/// a vector to store the different verytex buffer objects.
			std::vector<std::shared_ptr<VertexBuffer> > m_Buffers;
			/// The vetex count from the vbo.
			size_t m_VertCount;
			bool m_Dirty;
			/// A vector to store the planes for use in convex collider.
			std::vector<struct bu::ConvexPlane> m_ConvexPlanes;

	};
}