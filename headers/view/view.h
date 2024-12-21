#ifndef VIEW_H
#define VIEW_H


#include <string>
#include <crow.h>


class View
{
public:
	static void load_static_file(crow::response& res, const std::string& fileName);

	static void render(crow::response& res, const crow::request& req, const std::string& templateName, const crow::mustache::context& ctx = {});
};


#endif
