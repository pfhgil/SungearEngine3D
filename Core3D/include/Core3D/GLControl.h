#include <glad.h>
#include <iostream>
#include <vector>
#include <map>
#include "../../../GLFW/deps/linmath.h"

using namespace std;

namespace Core3D
{
	namespace GLC 
	{
		class GLBuffer 
		{
			private:
				GLuint _handler = 0;
				GLenum _type = GL_ARRAY_BUFFER;
			
			public:
				GLBuffer() : GLBuffer(GL_ARRAY_BUFFER) {}
				GLBuffer(GLenum type);
				~GLBuffer();

				GLBuffer* Bind();
				GLBuffer* Data(GLsizeiptr size, const void* data, GLenum type = GL_DYNAMIC_DRAW);
				GLBuffer* Clear();
		};


		class GLShader 
		{
			private:
				GLuint _programHandler = 0;

				map<std::string, GLint> _uniforms = map<std::string, GLint>();
				map<std::string, GLint> _attribs = map<std::string, GLint>();

				GLShader* getUniforms();
				GLShader* getAttribs();

				GLint getLocation(string name) 
				{ 
					if (!ContainsUniform(name)) { throw exception("BRUH"); }
					return _uniforms[name];
				}

				static const GLsizei bufferSize = 16;
			public:
				GLShader();
				GLShader(string shaderCode);
				~GLShader();

				GLShader* Use() { glUseProgram(_programHandler); return this; }

				// ���������� �������� (��� ����� ������ ��������)
				static shared_ptr<vector<GLuint>> Compile(vector<tuple<string, GLenum>>& arr);

				//�������� ��������� � �������� � ���� �������� 
				GLShader* BuildProgram(vector<GLuint>& shaders);

				GLShader* LinkProgram() { glLinkProgram(_programHandler); return this; }

				GLint getAttribLocation(string name) { return _attribs[name]; }// ��������� ����� ���� ����������� ������� ���������� ����������

				bool ContainsUniform(string name) { return _uniforms.find(name) != _uniforms.end(); }

				// ������ ��� �� ������ uniform-� ������ �����
				void uMat4x4(string name, mat4x4 value) { glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, (const GLfloat*) value); }

				bool ContainsAttrib(string name) { return _attribs.find(name) != _attribs.end(); }
				// ������ ���������
				// TODO: ������� ��������� ����������
			
		};


		struct GLVertexArrayAttribute
		{
			string name;
			GLBuffer* buffer;
			unsigned int size;
			unsigned int count;
			GLenum type;
		};

		class GLVertexArray
		{
			private:
				GLuint _handler = 0;
				GLShader* _program = nullptr;
				// <<name, Buffer, dataSize, dataCount, dataType>>
				// dataSize - ������ ������ �� ���� �������
				vector<GLVertexArrayAttribute> _attribsData = vector<GLVertexArrayAttribute>();
			public:
				GLVertexArray() { glGenVertexArrays(1, &_handler); }
				GLVertexArray(GLShader* shader) : GLVertexArray() { SetProgram(shader); }
				~GLVertexArray() {};

				GLVertexArray* SetProgram(GLShader* program) { _program = program; return this;}
				GLVertexArray* Bind() { glBindVertexArray(_handler); return this; }

				GLVertexArray* PutAttrib(GLVertexArrayAttribute attribute);

				GLVertexArray* BuildAttribs();
		};
	}
}