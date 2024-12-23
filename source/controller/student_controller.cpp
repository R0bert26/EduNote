#include <vector>
#include "../../headers/controller/student_controller.h"
#include "../../headers/model/session.h"
#include "../../headers/service/JsonService.h"
#include "../../headers/model/enrollment.h"
#include "../../headers/model/course.h"


void StudentController::run(crow::response& res, const crow::request& req)
{
	Student student(
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

	if (action == "get_student_enrollments")
	{
		get_student_enrollments(res, data, student);
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


void StudentController::get_student_enrollments(crow::response& res, crow::json::rvalue& data, Student& student)
{
	try
	{
		std::vector<Enrollment> enrollments = student.get_enrollments();
		std::vector<crow::json::wvalue> enrollmentsJson;

		for (auto& enrollment : enrollments)
		{
			crow::json::wvalue enrollmentJson;
			enrollmentJson["course_name"] = Course::get_course_name(enrollment.get_course_id());
			enrollmentJson["student_grade"] = enrollment.get_grade();

			enrollmentsJson.emplace_back(enrollmentJson);
		}

		crow::json::wvalue response;
		response["status"] = "success";
		response["student_name"] = Student::get_full_name(student.get_id());
		response["enrollments"] = std::move(enrollmentsJson);

		res.code = 200;
		res.set_header("Content-Type", "application/json");
		res.write(response.dump());
		res.end();
	}
	catch (const std::exception& err)
	{
		JsonService::create_error_response(res, "failed", err.what(), 500);
	}
}


void StudentController::logout(crow::response& res)
{
	Session::logout();

	crow::json::wvalue response;
	response["status"] = "success";

	res.code = 200;
	res.set_header("Content-Type", "application/json");
	res.write(response.dump());
	res.end();
}
