#include "router.h"
#include "view.h"
#include "login_controller.h"

void Router::init_routes(crow::SimpleApp& app)
{
	LoginController loginController;

	CROW_ROUTE(app, "/").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([&loginController](const crow::request& req)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				return View::load_html_file("login.html");
			}
			else if (req.method == crow::HTTPMethod::POST)
			{
				// TODO 
			}

			return crow::response(405, "Method Not Allowed");
		});

	CROW_ROUTE(app, "/login.css").methods(crow::HTTPMethod::GET)([](const crow::request& req)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				return View::load_css_file("login.css");
			}

			return crow::response(405, "Method Not Allowed");
		});
}