#include "../../headers/controller/professor_controller.h"
#include "../../headers/model/session.h"


void ProfessorController::run(crow::response& res, const crow::request& req)
{
	auto params = req.get_body_params();
	std::string action = params.get("action");

	if (action == "add_course")
	{
		std::string courseName = params.get("course");
		crow::mustache::context ctx;
		ctx["course"] = courseName;

		res.body = crow::mustache::load("professor.html").render_string(ctx);
		res.code = 200;
		res.set_header("Content-Type", "text/html");
		res.end();
	}
	else if (action == "logout")
	{
		Session::logout();

		res.set_header("Location", "/");
		res.code = 302;
		res.end();
	}
}
