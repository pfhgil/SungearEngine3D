#include <Core3D/GLControl.h>

using namespace Core3D::GLC;


GLVertexArray* GLVertexArray::BuildAttribs() {//FIXME: загрузка с разных буферов
	int stride = 0;
	for (auto a : _attribsData) {
		stride += a.size;
	}
	long offset = 0;
	for (auto a : _attribsData) {
		GLuint attrLocation = _program->getAttribLocation(a.name);
		glEnableVertexAttribArray(attrLocation);
		a.buffer->Bind();
		glVertexAttribPointer(attrLocation, a.count, a.type, GL_FALSE, stride, (void*)offset);
		offset += a.size;
	}
	return this;
}

GLVertexArray* GLVertexArray::PutAttrib(GLVertexArrayAttribute attrib)
{
	this->_attribsData.push_back(attrib);
	return this;
}