#include "../../headers/controller/professor_controller.h"
#include "../../headers/model/session.h"
#include "../../headers/service//JsonService.h"
#include "../../headers/model/professor.h"
#include "../../headers/model/course.h"
#include "../../headers/model/enrollment.h"
#include "../../headers/model/student.h"
#include <vector>


void ProfessorController::run(crow::response& res, const crow::request& req)
{
	Professor professor(
		Session::get_current_session().get_id(),
		Session::get_current_session().get_first_name(),
		Session::get_current_session().get_last_name(),
		Session::get_current_session().get_email(),
		Session::get_current_session().get_role());

	crow::json::rvalue data = crow::json::load(req.body);
	if (!data)
	{
		JsonService::create_error_response(res, "failed", "Invalid JSON", 400);
		return;
	}

	std::string action = data.has("action") ? data["action"].s() : std::string("");
	if (action == "")
	{
		JsonService::create_error_response(res, "failed", "Invalid Action", 400);
		return;
	}

	if (action == "add_course")
	{
		add_course(res, data, professor);
	}
	else if (action == "get_courses")
	{
		get_courses(res, data, professor);
	}
	else if (action == "delete_course")
	{
		delete_course(res, data, professor);
	}
	else if (action == "add_student")
	{
		add_student(res, data, professor);
	}
	else if (action == "get_enrollments")
	{
		get_enrollments(res, data, professor);
	}
	else if (action == "delete_enrollment")
	{
		delete_enrollment(res, data, professor);
	}
	else if (action == "logout")
	{
		logout(res);
	}
}


void ProfessorController::add_course(crow::response& res, crow::json::rvalue& data, Professor& professor)
{
	std::string courseName = data.has("course") ? data["course"].s() : std::string("");
	if (courseName == "")
	{
		JsonService::create_error_response(res, "failed", "Invalid Course Name", 400);
		return;
	}

	bool status = professor.add_course(courseName);
	if (!status)
	{
		JsonService::create_error_response(res, "failed", "Error Adding Course", 400);
		return;
	}

	std::vector<Course> courses = Course::get_courses(professor.get_id());

	std::vector<crow::json::wvalue> coursesJson;
	for (int i = 0; i < courses.size(); i++)
	{
		crow::json::wvalue courseJson;
		courseJson["id"] = courses[i].get_id();
		courseJson["name"] = courses[i].get_name();

		coursesJson.emplace_back(courseJson);
	}

	crow::json::wvalue response;
	response["status"] = "success";
	response["message"] = "Course added successfully";
	response["courses"] = std::move(coursesJson);

	res.code = 200;
	res.set_header("Content-Type", "application/json");
	res.write(response.dump());
	res.end();
}


void ProfessorController::get_courses(crow::response& res, crow::json::rvalue& data, Professor& professor)
{
	std::vector<Course> courses = Course::get_courses(professor.get_id());

	std::vector<crow::json::wvalue> coursesJson;
	for (int i = 0; i < courses.size(); i++)
	{
		crow::json::wvalue courseJson;
		courseJson["id"] = courses[i].get_id();
		courseJson["name"] = courses[i].get_name();

		coursesJson.emplace_back(courseJson);
	}
	
	crow::json::wvalue response;
	response["courses"] = std::move(coursesJson);
	response["status"] = "success";

	res.code = 200;
	res.set_header("Content-Type", "application/json");
	res.write(response.dump());
	res.end();
}


void ProfessorController::delete_course(crow::response& res, crow::json::rvalue& data, Professor& professor)
{
	int courseId = data.has("course_id") ? data["course_id"].i() : 0;
	if (courseId == 0)
	{
		JsonService::create_error_response(res, "failed", "Invalid Course ID", 400);
		return;
	}

	bool status = professor.delete_course(courseId);
	if (!status)
	{
		JsonService::create_error_response(res, "failed", "Error Deleting Course", 400);
		return;
	}

	std::vector<Course> courses = Course::get_courses(professor.get_id());

	std::vector<crow::json::wvalue> coursesJson;
	for (int i = 0; i < courses.size(); i++)
	{
		crow::json::wvalue courseJson;
		courseJson["id"] = courses[i].get_id();
		courseJson["name"] = courses[i].get_name();

		coursesJson.emplace_back(courseJson);
	}

	crow::json::wvalue response;
	response["status"] = "success";
	response["message"] = "Course deleted successfully";
	response["courses"] = std::move(coursesJson);

	res.code = 200;
	res.set_header("Content-Type", "application/json");
	res.write(response.dump());
	res.end();
}


void ProfessorController::add_student(crow::response& res, crow::json::rvalue& data, Professor& professor)
{
	std::string studentEmail = data.has("student_email") ? data["student_email"].s() : std::string("");
	if (studentEmail == "")
	{
		JsonService::create_error_response(res, "failed", "Invalid Student Email", 400);
		return;
	}

	int courseId = data.has("course_id") ? data["course_id"].i() : -1;
	if (courseId == -1)
	{
		JsonService::create_error_response(res, "failed", "Invalid Course ID", 400);
		return;
	}

	auto status = professor.add_enrollments(studentEmail, courseId);
	if (!status)
	{
		JsonService::create_error_response(res, "failed", "Error Adding Student", 400);
		return;
	}

	std::vector<Enrollment> enrollments = Enrollment::get_course_enrollments(courseId);

	std::vector<crow::json::wvalue> enrollmentsJson;
	for (auto& enrollment : enrollments)
	{
		crow::json::wvalue enrollmentJson;
		enrollmentJson["id"] = enrollment.get_id();
		enrollmentJson["student_name"] = Student::get_full_name(enrollment.get_student_id());
		enrollmentJson["student_grade"] = enrollment.get_grade();

		enrollmentsJson.emplace_back(enrollmentJson);
	}

	crow::json::wvalue response;
	response["status"] = "success";
	response["message"] = "Student added successfully";
	response["enrollments"] = std::move(enrollmentsJson);

	res.code = 200;
	res.set_header("Content-Type", "application/json");
	res.write(response.dump());
	res.end();
}

void ProfessorController::get_enrollments(crow::response& res, crow::json::rvalue& data, Professor& professor)
{
	int courseId = data.has("course_id") ? data["course_id"].i() : -1;
	if (courseId == -1)
	{
		JsonService::create_error_response(res, "failed", "Invalid Course ID", 400);
		return;
	}

	std::vector<Enrollment> enrollments = Enrollment::get_course_enrollments(courseId);

	std::vector<crow::json::wvalue> enrollmentsJson;
	for (auto& enrollment : enrollments)
	{
		crow::json::wvalue enrollmentJson;
		enrollmentJson["id"] = enrollment.get_id();
		enrollmentJson["student_name"] = Student::get_full_name(enrollment.get_student_id());
		enrollmentJson["student_grade"] = enrollment.get_grade();

		enrollmentsJson.emplace_back(enrollmentJson);
	}

	crow::json::wvalue response;
	response["status"] = "success";
	response["course_name"] = Course::get_course_name(courseId);
	response["enrollments"] = std::move(enrollmentsJson);

	res.code = 200;
	res.set_header("Content-Type", "application/json");
	res.write(response.dump());
	res.end();
}

void ProfessorController::delete_enrollment(crow::response& res, crow::json::rvalue& data, Professor& professor)
{
	int enrollmentId = data.has("enrollment_id") ? data["enrollment_id"].i() : -1;
	if (enrollmentId == -1)
	{
		JsonService::create_error_response(res, "failed", "Invalid Enrollment ID", 400);
		return;
	}

	int courseId = data.has("course_id") ? data["course_id"].i() : -1;
	if (courseId == -1)
	{
		JsonService::create_error_response(res, "failed", "Invalid Course ID", 400);
		return;
	}

	auto status = professor.delete_enrollment(enrollmentId);
	if (!status)
	{
		JsonService::create_error_response(res, "failed", "Error Deleting Enrollment", 400);
		return;
	}

	std::vector<Enrollment> enrollments = Enrollment::get_course_enrollments(courseId);

	std::vector<crow::json::wvalue> enrollmentsJson;
	for (auto& enrollment : enrollments)
	{
		crow::json::wvalue enrollmentJson;
		enrollmentJson["id"] = enrollment.get_id();
		enrollmentJson["student_name"] = Student::get_full_name(enrollment.get_student_id());
		enrollmentJson["student_grade"] = enrollment.get_grade();

		enrollmentsJson.emplace_back(enrollmentJson);
	}

	crow::json::wvalue response;
	response["status"] = "success";
	response["message"] = "Enrollment deleted successfully";
	response["course_name"] = Course::get_course_name(courseId);
	response["enrollments"] = std::move(enrollmentsJson);

	res.code = 200;
	res.set_header("Content-Type", "application/json");
	res.write(response.dump());
	res.end();
}


void ProfessorController::logout(crow::response& res)
{
	Session::logout();

	crow::json::wvalue response;
	response["status"] = "success";
	
	res.code = 200;
	res.set_header("Content-Type", "application/json");
	res.write(response.dump());
	res.end();
}
