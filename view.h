#ifndef VIEW_H
#define VIEW_H

#include <crow.h>
#include <string>

class View
{
public:
	static crow::response load_html_file(const std::string& fileName);

	static crow::response load_css_file(const std::string& fileName);
};

#endif