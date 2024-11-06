#include "router.h"
#include "login_controller.h"
#include "view.h"

void Router::init_routes(crow::SimpleApp& app)
{
	LoginController loginController;

	CROW_ROUTE(app, "/").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([&loginController](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				res.code = 200;
				res.body = View::load_file("login.html");

				if (res.body.empty())
				{
					res.code = 404;
					res.body = "Page Not Found";
				}
			}
			else if (req.method == crow::HTTPMethod::POST)
			{
				loginController.login(req, res);
			}
			else
			{
				res.code = 405;
				res.body = "Method Not Allowed";
			}

			res.end();
		});

	CROW_ROUTE(app, "/admin").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				res.code = 200;
				res.body = View::load_file("admin.html");

				if (res.body.empty())
				{
					res.code = 404;
					res.body = "Page Not Found";
				}
			}
			else
			{
				res.code = 405;
				res.body = "Method Not Allowed";
			}

			res.end();
		});

	CROW_ROUTE(app, "/student").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				res.code = 200;
				res.body = View::load_file("student.html");

				if (res.body.empty())
				{
					res.code = 404;
					res.body = "Page Not Found";
				}
			}
			else
			{
				res.code = 405;
				res.body = "Method Not Allowed";
			}

			res.end();
		});

	CROW_ROUTE(app, "/professor").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				res.code = 200;
				res.body = View::load_file("professor.html");

				if (res.body.empty())
				{
					res.code = 404;
					res.body = "Page Not Found";
				}
			}
			else
			{
				res.code = 405;
				res.body = "Method Not Allowed";
			}

			res.end();
		});

	CROW_ROUTE(app, "/admin.css").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				res.code = 200;
				res.body = View::load_file("admin.css");

				if (res.body.empty())
				{
					res.code = 404;
					res.body = "Page Not Found";
				}
			}
			else
			{
				res.code = 405;
				res.body = "Method Not Allowed";
			}

			res.end();
		});

	CROW_ROUTE(app, "/student.css").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				res.code = 200;
				res.body = View::load_file("student.css");

				if (res.body.empty())
				{
					res.code = 404;
					res.body = "Page Not Found";
				}
			}
			else
			{
				res.code = 405;
				res.body = "Method Not Allowed";
			}

			res.end();
		});

	CROW_ROUTE(app, "/login.css").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				res.code = 200;
				res.body = View::load_file("login.css");

				if (res.body.empty())
				{
					res.code = 404;
					res.body = "Page Not Found";
				}
			}
			else
			{
				res.code = 405;
				res.body = "Method Not Allowed";
			}

			res.end();
		});

	CROW_ROUTE(app, "/professor.css").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				res.code = 200;
				res.body = View::load_file("professor.css");

				if (res.body.empty())
				{
					res.code = 404;
					res.body = "Page Not Found";
				}
			}
			else
			{
				res.code = 405;
				res.body = "Method Not Allowed";
			}

			res.end();
		});
}