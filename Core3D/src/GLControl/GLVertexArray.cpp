#include <Core3D/GLControl.h>

using namespace Core3D::GLC;


void GLVertexArray::BuildAttribs(GLShader& shader) {//FIXME: загрузка с разных буферов
	int stride = 0;
	for (auto a : _attribsData) {
		stride += a.size;
	}
	long offset = 0;
	for (auto a : _attribsData) {
		GLuint attrLocation = shader.getAttribLocation(a.name);
		glEnableVertexAttribArray(attrLocation);
		a.buffer->Bind();
		glVertexAttribPointer(attrLocation, a.count, a.type, GL_FALSE, stride, (void*)offset);
		offset += a.size;
	}
}