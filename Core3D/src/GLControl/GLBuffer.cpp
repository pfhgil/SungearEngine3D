#include <Core3D/GLControl.h>
#include <glad.h>

using namespace Core3D::GLC;


//TODO: перенести почти всю обёрточную логику в заголовочный файл

GLBuffer::GLBuffer(GLenum type)
{
	glGenBuffers(1, &_handler);
	_type = type;
}
GLBuffer::~GLBuffer()
{
	glDeleteBuffers(1, &_handler);
}

GLBuffer* GLBuffer::Bind() 
{
	glBindBuffer(_type, _handler);
	return this;
}
GLBuffer* GLBuffer::Data(GLsizeiptr size, const void* data, GLenum usage) { // Реализовать больше перегрузок метода
	glBufferData(_type, size, data, usage);
	return this;
}
GLBuffer* GLBuffer::Clear() 
{
	glBufferData(_type, 0, nullptr, GL_DYNAMIC_DRAW);
	return this;
}
