#include <Core3D/GLControl.h>

using namespace Core3D::GLC;


GLVertexArray* GLVertexArray::BuildAttribs() {//FIXME: загрузка с разных буферов
	int stride = 0;
	for (auto v : _attribsData) {
		auto [name, buffer, dataSize, dataCount, dataType] = v;
		stride += dataSize;
	}
	long offset = 0;
	for (auto v : _attribsData) {
		auto [name, buffer, dataSize, dataCount, dataType] = v;
		GLuint attrLocation = _program->getAttribLocation(name);
		glEnableVertexAttribArray(attrLocation);
		buffer->Bind();
		glVertexAttribPointer(attrLocation, dataCount, dataType, GL_FALSE, stride, (void*)offset);
		offset += dataSize;
	}
	return this;
}