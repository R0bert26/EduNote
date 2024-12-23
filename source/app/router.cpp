#include "../../headers/app/router.h"
#include "../../headers/controller/login_controller.h"
#include "../../headers/controller/admin_controller.h"
#include "../../headers/controller/student_controller.h"
#include "../../headers/controller/professor_controller.h"
#include "../../headers/app/error.h"
#include "../../headers/view/view.h"
#include "../../headers/model/session.h"


void Router::init_routes(crow::SimpleApp& app)
{
	CROW_ROUTE(app, "/").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([](const crow::request& req, crow::response& res)
		{
			if (req.method == crow::HTTPMethod::GET)
			{
				View::render(res, req, "login.html");
			}
			else if (req.method == crow::HTTPMethod::POST)
			{
				LoginController::login(req, res);
			}
		});

	CROW_ROUTE(app, "/admin").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([](const crow::request& req, crow::response& res)
		{
			if (Session::get_current_session().get_role() == "admin")
			{
				if (req.method == crow::HTTPMethod::GET)
				{
					View::render(res, req, "admin.html");
				}
				else if (req.method == crow::HTTPMethod::POST)
				{
					AdminController::run(res, req);
				}
			}
			else
			{
				Error::generate_error_page(res, 401, "Access Unauthorized");
			}
		});

	CROW_ROUTE(app, "/student").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([](const crow::request& req, crow::response& res)
		{
			if (Session::get_current_session().get_role() == "student")
			{
				if (req.method == crow::HTTPMethod::GET)
				{
					View::render(res, req, "student.html");
				}
				else if (req.method == crow::HTTPMethod::POST)
				{
					StudentController::run(res, req);
				}
			}
			else
			{
				Error::generate_error_page(res, 401, "Access Unauthorized");
			}
		});

	CROW_ROUTE(app, "/professor").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([](const crow::request& req, crow::response& res)
		{
			if (Session::get_current_session().get_role() == "professor")
			{
				if (req.method == crow::HTTPMethod::GET)
				{
					View::render(res, req, "professor.html");
				}
				else if (req.method == crow::HTTPMethod::POST)
				{
					ProfessorController::run(res, req);
				}
			}
			else
			{
				Error::generate_error_page(res, 401, "Access Unauthorized");
			}
		});

	CROW_ROUTE(app, "/static/<string>").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res, const std::string& cssFile)
		{
			View::load_static_file(res, "resources/static/" + cssFile);
		});

	CROW_ROUTE(app, "/script/<string>").methods(crow::HTTPMethod::GET)([](const crow::request& req, crow::response& res, const std::string& jsFile)
		{
			View::load_static_file(res, "resources/script/" + jsFile);
		});

	CROW_ROUTE(app, "/<path>")([](const crow::request& req, crow::response& res, const auto& path)
		{
			Error::generate_error_page(res, 404, "Page Not Found");
		});
}
