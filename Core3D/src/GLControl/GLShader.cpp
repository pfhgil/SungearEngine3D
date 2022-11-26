#include <Core3D/GLControl.h>
#include <glad.h>
#include <iostream>

using namespace Core3D::GLC;
using namespace std;

GLShader::GLShader() {

}
GLShader::GLShader(string computeShaderCode) {
	this->BuildProgram(this->Compile(computeShaderCode, GL_COMPUTE_SHADER));
	getUniforms(); 
	getAttribs();
}
GLShader::GLShader(string fragmentSource, string vertexSource) {
	vector<tuple<string, GLenum>> shaders = { make_tuple(fragmentSource, GL_FRAGMENT_SHADER), make_tuple(vertexSource, GL_VERTEX_SHADER) };
	this->BuildProgram(*this->Compile(shaders));	
	getUniforms(); 
	getAttribs();
}
GLShader::~GLShader() {
	glDeleteProgram(_programHandler);
}

GLuint GLShader::Compile(string code, GLenum type) {
	GLuint shader = glCreateShader(type);
	const char* c = code.c_str();
	glShaderSource(shader, 1, &c, NULL);
	glCompileShader(shader);
	return shader;
}

shared_ptr<vector<GLuint>> GLShader::Compile(vector<tuple<string, GLenum>>& code) {
	shared_ptr<vector<GLuint>> result(new vector<GLuint>);
	for(auto& el : code)
	{
		auto [code, type] = el;
		GLuint shader = glCreateShader(type);
		const char* c = code.c_str();
		glShaderSource(shader, 1, &c, NULL);
		glCompileShader(shader);
		result->push_back(shader);
	}
	return result;
}

GLShader* GLShader::BuildProgram(GLuint shader) {
	_programHandler = glCreateProgram();
	glAttachShader(_programHandler, shader);
		glLinkProgram(_programHandler);
	glDetachShader(_programHandler, shader);
	return this;
}

GLShader* GLShader::BuildProgram(vector<GLuint>& shaders) {
	_programHandler = glCreateProgram();
	for (auto shader : shaders) {
		glAttachShader(_programHandler, shader);
	}
	glLinkProgram(_programHandler);
	for (auto shader : shaders) {
		glDetachShader(_programHandler, shader);
	}
	return this;
}


GLShader* GLShader::getUniforms() {
	int count; 
	glGetProgramiv(_programHandler, GL_ACTIVE_UNIFORMS, &count);

	for (int i = 0; i < count; i++) 
	{
		GLsizei len; GLint size; GLenum type; GLchar name[bufferSize];
		glGetActiveUniform(_programHandler, i, bufferSize, &len, &size, &type, name);
		_uniforms[name] = glGetUniformLocation(_programHandler, name);
	}
	return this;
}

GLShader* GLShader::getAttribs() {
	int count;
	glGetProgramiv(_programHandler, GL_ACTIVE_ATTRIBUTES, &count);
	for (int i = 0; i < count; i++)
	{
		GLsizei len; GLint size; GLenum type; GLchar name[bufferSize];
		glGetActiveAttrib(_programHandler, i, bufferSize, &len, &size, &type, name);
		_attribs[name] = glGetAttribLocation(_programHandler, name);
	}
	return this;
}

