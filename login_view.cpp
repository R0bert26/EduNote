#include "login_view.h"
#include <crow.h>
#include <fstream>

crow::response LoginView::render()
{
	std::ifstream file("login.html");

	if (!file)
	{
		return crow::response(404);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	crow::response res(buffer.str());
	res.set_header("Content-Type", "text/html");

	return res;
}