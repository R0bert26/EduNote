#include "router.h"
#include "login_controller.h"
#include "error.h"
#include "view.h"

void Router::init_routes(crow::SimpleApp& app)
{
	LoginController loginController;

	CROW_ROUTE(app, "/").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([&loginController](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				res.code = 200;
				res.body = crow::mustache::load_text("login.html");
				res.set_header("Content-Type", "text/html");

				if (res.body.empty())
				{
					Error::generate_error_page(res, 404, "Page Not Found");
				}
			}
			else if (req.method == crow::HTTPMethod::POST)
			{
				loginController.login(req, res);
			}

			res.end();
		});

	CROW_ROUTE(app, "/admin").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				res.code = 200;
				res.body = crow::mustache::load_text("admin.html");
				res.set_header("Content-Type", "text/html");

				if (res.body.empty())
				{
					Error::generate_error_page(res, 404, "Page Not Found");
				}
			}

			res.end();
		});

	CROW_ROUTE(app, "/student").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				res.code = 200;
				res.body = crow::mustache::load_text("student.html");
				res.set_header("Content-Type", "text/html");

				if (res.body.empty())
				{
					Error::generate_error_page(res, 404, "Page Not Found");
				}
			}

			res.end();
		});

	CROW_ROUTE(app, "/professor").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				res.code = 200;
				res.body = crow::mustache::load_text("professor.html");
				res.set_header("Content-Type", "text/html");

				if (res.body.empty())
				{
					Error::generate_error_page(res, 404, "Page Not Found");
				}
			}

			res.end();
		});

	CROW_ROUTE(app, "/static/<string>").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res, const std::string& cssFile)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				res.code = 200;
				res.body = View::load_css_file(cssFile);
				res.set_header("Content-Type", "text/css");

				if (res.body.empty())
				{
					Error::generate_error_page(res, 404, "Page Not Found");
				}
			}

			res.end();
		});
}