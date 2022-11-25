#include <Core3D/GLControl/GLBuffer.h>
#include <glad.h>

using namespace Core3D::GLC;

GLBuffer::GLBuffer(GLenum type) {
	glGenBuffers(1, &_handler);
	_type = type;
}

GLBuffer* GLBuffer::Bind() {
	glBindBuffer(_type, _handler);
	return this;
}
GLBuffer* GLBuffer::BufferData(GLsizeiptr size, const void* data, GLenum usage) {
	//Bind(); // FIXME: надо ли делать автоюз, мне кажется нет
	glBufferData(_type, size, data, usage);
	return this;
}