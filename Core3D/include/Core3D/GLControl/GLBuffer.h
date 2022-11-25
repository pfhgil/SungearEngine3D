#include <glad.h>

namespace Core3D {
	namespace GLC {
		class GLBuffer {
		private:
			GLuint _handler;
			GLenum _type= GL_DYNAMIC_DRAW;
		public:
			GLBuffer() { }
			GLBuffer(GLenum type);
			~GLBuffer();

			GLBuffer* Bind();
			GLBuffer* BufferData(GLsizeiptr size, const void* data, GLenum usage= GL_DYNAMIC_DRAW);
		};
	}
}