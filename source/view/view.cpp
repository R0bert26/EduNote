#include <iostream>
#include <fstream>
#include <sstream>
#include "../../headers/view/view.h"
#include "../../headers/app/error.h"


void View::load_css_file(crow::response& res, const std::string& filePath)
{
	std::ifstream file(filePath);

	if (!file.is_open())
	{
		res.code = 404;
		res.body = "";
		res.set_header("Content-Type", "text/plain");
		res.end();
	}
	else
	{
		std::stringstream buffer;
		buffer << file.rdbuf();

		res.code = 200;
		res.body = buffer.str();
		res.set_header("Content-Type", "text/css");
		res.end();
	}
}


void View::render(crow::response& res, const crow::request& req, const std::string& templateName, const crow::mustache::context& ctx)
{
	res.body = crow::mustache::load(templateName).render_string(ctx);

	if (res.body.empty())
	{
		Error::generate_error_page(res, 404, "HTML File Not Found");
	}
	else
	{
		res.code = 200;
		res.set_header("Content-Type", "text/html");
		res.end();
	}
}
