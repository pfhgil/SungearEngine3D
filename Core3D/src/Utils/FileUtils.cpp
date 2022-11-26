#include <iostream>
#include <memory>
#include <fstream>
#include <Core3D/Utils.h>

using namespace Core3D::Utils;

std::string FileUtils::ReadAllFile(const std::string path)
{
	std::string text = "";

	std::ifstream file(path);

	if(file.is_open()) 
	{
		char c = '\0';
		while(file.get(c) && c != '\0')
		{
			text += c;
		}
	}

	file.close();
		
	return text;
}	