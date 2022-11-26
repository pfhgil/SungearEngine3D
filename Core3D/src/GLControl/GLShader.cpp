#include <Core3D/GLControl.h>
#include <glad.h>
#include <iostream>

using namespace Core3D::GLC;
using namespace std;

GLShader::GLShader()
{

}

GLShader::GLShader(string shaderCode) 
{
	string vertexShaderCode = "#define VERTEX\n" + shaderCode;
	string fragmentShaderCode = "#define FRAGMENT\n" + shaderCode;

	vector<tuple<string, GLenum>> shaders = {make_tuple(vertexShaderCode, GL_VERTEX_SHADER), make_tuple(fragmentShaderCode, GL_FRAGMENT_SHADER)};

	this->BuildProgram(*this->Compile(shaders));
	getUniforms(); 
	getAttribs();
}

GLShader::~GLShader() 
{
	glDeleteProgram(_programHandler);
}

shared_ptr<vector<GLuint>> GLShader::Compile(vector<tuple<string, GLenum>>& code)
{
	shared_ptr<vector<GLuint>> result(new vector<GLuint>);
	for(auto& el : code)
	{
		auto[code, type] = el;
		GLuint shader = glCreateShader(type);
		const char* c = code.c_str();
		glShaderSource(shader, 1, &c, nullptr);
		glCompileShader(shader);
		result->push_back(shader);
	}
	return result;
}

GLShader* GLShader::BuildProgram(vector<GLuint>& shaders)
{
	_programHandler = glCreateProgram();

	for (auto shader : shaders) 
	{
		glAttachShader(_programHandler, shader);
	}

	glLinkProgram(_programHandler);

	for (auto shader : shaders)
	{
		glDetachShader(_programHandler, shader);
	}
	return this;
}


GLShader* GLShader::getUniforms() 
{
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

GLShader* GLShader::getAttribs() 
{
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

