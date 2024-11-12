#include "view.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string View::load_css_file(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << fileName << std::endl;

		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	return buffer.str();
}