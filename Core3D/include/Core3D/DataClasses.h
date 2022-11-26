#pragma once

#include <iostream>

namespace Core3D
{
	namespace DataClasses
	{
		class Data
		{
			Data* Load(std::string path) { return this; }
			Data* Load(std::iostream stream) { return this; }
			Data* Set(Data* data) { return this; }
		};

		class ShaderData : Data
		{
			private:
			std::string _sourceCode = "";

			public:
			override ShaderData* Load(std::string path)
			{

			}
		};
	}
}