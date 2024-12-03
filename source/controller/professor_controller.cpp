#include "../../headers/controller/professor_controller.h"
#include "../../headers/model/session.h"


void ProfessorController::run(crow::response& res, const crow::request& req)
{
	auto params = req.get_body_params();
	std::string action = params.get("action");

	if (action == "logout")
	{
		Session::logout();

		res.set_header("Location", "/");
		res.code = 302;
		res.end();
	}
}
