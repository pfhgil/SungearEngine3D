#include <glad.h>
#include <iostream>
#include <vector>
#include <map>
#include <stdarg.h>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

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

				// Компиляция шейдеров (для своих сборок шейдеров)
				static shared_ptr<vector<GLuint>> Compile(vector<tuple<string, GLenum>>& arr);

				//Создание программы и линковка к нему шейдеров 
				GLShader* BuildProgram(vector<GLuint>& shaders);

				GLShader* LinkProgram() { glLinkProgram(_programHandler); return this; }

				GLint getAttribLocation(string name) { return _attribs[name]; }// Временный метод пока отсутствует система компоновки аттрибутов

				bool ContainsUniform(string name) { return _uniforms.find(name) != _uniforms.end(); }

				// Методы что бы задать uniform-ы разных типов
				void uMat4x4(string name, mat4 value) { glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, &value[0][0]); }

				bool ContainsAttrib(string name) { return _attribs.find(name) != _attribs.end(); }
				// Задать аттрибуты
				// TODO: систему компновки аттрибутов
			
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
				// <<name, Buffer, dataSize, dataCount, dataType>>
				// dataSize - размер данных на одну вершину
				vector<GLVertexArrayAttribute> _attribsData;
			public:
				GLVertexArray() { glGenVertexArrays(1, &_handler); }
				~GLVertexArray() {};

				inline void Bind() { glBindVertexArray(_handler); }

				template<typename... Args>
				inline void PutAttribs(Args&... attribs) noexcept
				{
					_attribsData.insert(_attribsData.end(), {attribs...});
				};

			    void BuildAttribs(GLShader& shader);
		};
	}
}	