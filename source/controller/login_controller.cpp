#include "../../headers/controller/login_controller.h"
#include "../../headers/service/auth_service.h"
#include "../../headers/app/error.h"
#include "../../headers/model/session.h"
#include "../../headers/model/user.h"


void LoginController::login(const crow::request& req, crow::response& res)
{
	auto params = req.get_body_params();

	std::string email = params.get("email");
	std::string password = params.get("password");

	if (AuthService::check_auth(email, password))
	{
		User user = User::get_user(email);

		if (user.get_id() == 0)
		{
			Error::generate_error_page(res, 500, "Invalid User");
		}
		else
		{
			Session::create_session(user);

			if (user.get_role() == "admin")
			{
				res.set_header("Location", "/admin");
			}
			else if (user.get_role() == "student")
			{
				res.set_header("Location", "/student");
			}
			else if (user.get_role() == "professor")
			{
				res.set_header("Location", "/professor");
			}

			res.code = 302;
			res.end();
		}
	}
	else
	{
		Error::generate_error_page(res, 401, "Invalid Email or Password");
	}
}
