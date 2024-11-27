#ifndef VIEW_H
#define VIEW_H


#include <string>
#include <crow.h>


class View
{
public:
	static void load_css_file(crow::response& res, const std::string& fileName);

	static void render(crow::response& res, const crow::request& req, const std::string& templateName);

	static void render(crow::response& res, const crow::request& req, const std::string& templateName, crow::mustache::context& ctx);
};


#endif
