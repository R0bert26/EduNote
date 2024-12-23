#include "../../headers/controller/admin_controller.h"
#include "../../headers/model/admin.h"
#include "../../headers/app/error.h"
#include "../../headers/model/session.h"
#include "../../headers/service/JsonService.h"


void AdminController::run(crow::response& res, const crow::request& req)
{
	Admin admin(
		Session::get_current_session().get_id(),
		Session::get_current_session().get_first_name(),
		Session::get_current_session().get_last_name(),
		Session::get_current_session().get_email(),
		Session::get_current_session().get_role());

	crow::json::rvalue data = crow::json::load(req.body);
	if (!data)
	{
		JsonService::create_error_response(res, "failed", "Invalid JSON", 500);
		return;
	}

	std::string action = data.has("action") ? data["action"].s() : std::string("");
	if (action == "")
	{
		JsonService::create_error_response(res, "failed", "Invalid Action", 500);
		return;
	}

	if (action == "add_user")
	{
		add_user(res, data, admin);
	}
	else if (action == "delete_user")
	{
		delete_user(res, data, admin);
	}
	else if (action == "logout")
	{
		logout(res);
	}
	else
	{
		JsonService::create_error_response(res, "failed", "Invalid Action", 500);
		return;
	}
}

void AdminController::add_user(crow::response& res, crow::json::rvalue& data, Admin& admin)
{
	try
	{
		std::string firstName = data.has("first_name") ? data["first_name"].s() : std::string("");
		if (firstName == "")
		{
			JsonService::create_error_response(res, "failed", "Invalid First Name", 400);
			return;
		}

		std::string lastName = data.has("last_name") ? data["last_name"].s() : std::string("");
		if (lastName == "")
		{
			JsonService::create_error_response(res, "failed", "Invalid Last Name", 400);
			return;
		}

		std::string email = data.has("email") ? data["email"].s() : std::string("");
		if (email == "")
		{
			JsonService::create_error_response(res, "failed", "Invalid Email", 400);
			return;
		}

		std::string password = data.has("password") ? data["password"].s() : std::string("");
		if (password == "")
		{
			JsonService::create_error_response(res, "failed", "Invalid Password", 400);
			return;
		}

		std::string role = data.has("role") ? data["role"].s() : std::string("");
		if (role == "")
		{
			JsonService::create_error_response(res, "failed", "Invalid Role", 400);
			return;
		}

		admin.add_user(firstName, lastName, email, password, role);

		crow::json::wvalue response;
		response["status"] = "success";
		response["message"] = "User added successfully";

		res.code = 200;
		res.set_header("Content-Type", "application/json");
		res.write(response.dump());
		res.end();
	}
	catch (const std::exception& err)
	{
		JsonService::create_error_response(res, "failed", err.what(), 500);
		return;
	}
}

void AdminController::delete_user(crow::response& res, crow::json::rvalue& data, Admin& admin)
{
	try
	{
		std::string email = data.has("email") ? data["email"].s() : std::string("");
		if (email == "")
		{
			JsonService::create_error_response(res, "failed", "Invalid Email", 400);
			return;
		}

		admin.delete_user(email);

		crow::json::wvalue response;
		response["status"] = "success";
		response["message"] = "User deleted successfully";

		res.code = 200;
		res.set_header("Content-Type", "application/json");
		res.write(response.dump());
		res.end();
	}
	catch (const std::exception& err)
	{
		JsonService::create_error_response(res, "failed", err.what(), 500);
		return;
	}
}

void AdminController::logout(crow::response& res)
{
	Session::logout();

	crow::json::wvalue response;
	response["status"] = "success";

	res.code = 200;
	res.set_header("Content-Type", "application/json");
	res.write(response.dump());
	res.end();
}
