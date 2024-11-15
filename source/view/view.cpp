#include "../../headers/view/view.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string View::load_css_file(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filePath << std::endl;

		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	return buffer.str();
}