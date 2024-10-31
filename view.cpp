#include "view.h"
#include <fstream>
#include <sstream>

crow::response View::load_html_file(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (!file)
	{
		return crow::response(404, "Page Not Found");
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	crow::response res(buffer.str());
	res.set_header("Content-Type", "text/html");

	return res;
}

crow::response View::load_css_file(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (!file)
	{
		return crow::response(404, "Error loading CSS file");
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	crow::response res(buffer.str());
	res.set_header("Content-Type", "text/css");

	return res;
}