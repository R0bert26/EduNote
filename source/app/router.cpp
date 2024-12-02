#include "../../headers/app/router.h"
#include "../../headers/controller/login_controller.h"
#include "../../headers/app/error.h"
#include "../../headers/view/view.h"
#include "../../headers/model/session.h"


void Router::init_routes(crow::SimpleApp& app)
{
	LoginController loginController;

	CROW_ROUTE(app, "/").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([&loginController](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				View::render(res, req, "login.html");
			}
			else if (req.method == crow::HTTPMethod::POST)
			{
				loginController.login(req, res);
			}
			else
			{
				Error::generate_error_page(res, 405, "Method Not Allowed");
			}
		});

	CROW_ROUTE(app, "/admin").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([](const crow::request& req, crow::response& res)
		{
			if (Session::get_current_session().get_role() == "admin")
			{
				View::render(res, req, "admin.html");

				if (req.method == crow::HTTPMethod::POST)
				{
					res.code = 200;
					res.end();
				}
			}
			else
			{
				Error::generate_error_page(res, 401, "Access Unauthorized");
			}
		});

	CROW_ROUTE(app, "/student").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res)
		{
			if (Session::get_current_session().get_role() == "student")
			{
				if (req.method == crow::HTTPMethod::GET)
				{
					View::render(res, req, "student.html");
				}
				else
				{
					Error::generate_error_page(res, 405, "Method Not Allowed");
				}
			}
			else
			{
				Error::generate_error_page(res, 401, "Access Unauthorized");
			}
		});

	CROW_ROUTE(app, "/professor").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res)
		{
			if (Session::get_current_session().get_role() == "professor")
			{
				if (req.method == crow::HTTPMethod::GET)
				{
					View::render(res, req, "professor.html");
				}
				else
				{
					Error::generate_error_page(res, 405, "Method Not Allowed");
				}
			}
			else
			{
				Error::generate_error_page(res, 401, "Access Unauthorized");
			}
		});

	CROW_ROUTE(app, "/static/<string>").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res, const std::string& cssFile)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				View::load_css_file(res, "resources/static/" + cssFile);
			}
			else
			{
				Error::generate_error_page(res, 405, "Method Not Allowed");
			}
		});

	CROW_ROUTE(app, "/script/<string>").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res, const std::string& jsFile)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				View::load_css_file(res, "resources/script/" + jsFile);
			}
			else
			{
				Error::generate_error_page(res, 405, "Method Not Allowed");
			}
		});

	CROW_ROUTE(app, "/<path>")([](const crow::request& req, crow::response& res, const auto& path)
		{
			Error::generate_error_page(res, 404, "Page Not Found");
		});
}
