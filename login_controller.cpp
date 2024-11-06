#include "login_controller.h"
#include "user_service.h"

void LoginController::login(const crow::request& req, crow::response& res)
{
	auto params = req.get_body_params();

	std::string email = params.get("email");
	std::string password = params.get("password");

	if (UserService::check_auth(email, password))
	{
		User user = UserService::get_user(email, password);

		if (user.get_id() == 0)
		{
			res.code = 500;
			res.body = "Invalid User";
		}

		if (user.get_role() == "admin")
		{
			res.code = 302;
			res.set_header("Location", "/admin");
		}
		else if (user.get_role() == "student")
		{
			res.code = 302;
			res.set_header("Location", "/student");
		}
		else if (user.get_role() == "professor")
		{
			res.code = 302;
			res.set_header("Location", "/professor");
		}
	}
	else
	{
		res.code = 401;
		res.body = "Invalid Email or Password";
	}
}