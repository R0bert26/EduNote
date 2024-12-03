#include "../../headers/controller/admin_controller.h"
#include "../../headers/model/user.h"
#include "../../headers/app/error.h"
#include "../../headers/model/session.h"


void AdminController::run(crow::response& res, const crow::request& req)
{
	auto params = req.get_body_params();
	std::string action = params.get("action");

	if (action == "add_user")
	{
		bool status = User::add_user(params.get("first_name"), params.get("last_name"), params.get("email"), params.get("password"), params.get("role"));

		if (status)
		{
			res.set_header("Location", "/admin");
			res.code = 302;
			res.end();
		}
		else
		{
			Error::generate_error_page(res, 500, "Error adding user");
		}
	}
	else if (action == "delete_user")
	{
		bool status = User::delete_user(params.get("email"));
	
		if (status)
		{
			res.set_header("Location", "/admin");
			res.code = 302;
			res.end();
		}
		else
		{
			Error::generate_error_page(res, 500, "Error deleting user");
		}
	}
	else if (action == "logout")
	{
		Session::logout();

		res.set_header("Location", "/");
		res.code = 302;
		res.end();
	}
}
