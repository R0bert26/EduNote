#include "../../headers/model/professor.h"
#include "../../headers/model/student.h"
#include "../../headers/model/enrollment.h"


Professor::Professor(
	const int& id,
	const std::string& firstName,
	const std::string& lastName,
	const std::string& email,
	const std::string& role) :
	User(id, firstName, lastName, email, role) {}


void Professor::add_course(const std::string& courseName)
{
	try
	{
		Database::session() << "INSERT INTO courses (course_name, professor_id) VALUES (:courseName, :professorId)",
			soci::use(courseName), soci::use(this->get_id());
	}
	catch (const std::exception& err)
	{
		throw std::runtime_error(std::string("Error Adding Course: ") + err.what());
	}
}


void Professor::delete_course(const int& courseId)
{
	try
	{
		Database::session() << "DELETE FROM courses WHERE course_id = :courseId",
			soci::use(courseId);
	}
	catch (const std::exception& err)
	{
		throw std::runtime_error(std::string("Error Deleting Course: ") + err.what());
	}
}


void Professor::add_enrollment(const std::string& studentEmail, const int& courseId)
{
	try
	{
		User user = User::get_user(studentEmail);
		if (user.get_role() != "student")
		{
			throw std::runtime_error("Student Not Found");
		}

		Enrollment::add_enrollment(user.get_id(), courseId);
	}
	catch (const std::exception& err)
	{
		throw std::runtime_error(std::string("Error Adding Enrollments: ") + err.what());
	}
}


void Professor::delete_enrollment(const int& enrollmentId)
{
	try
	{
		Database::session() << "DELETE FROM enrollments WHERE enrollment_id = :enrollmentId",
			soci::use(enrollmentId);
	}
	catch (const std::exception& err)
	{
		throw std::runtime_error(std::string("Error Deleting Enrollment: ") + err.what());
	}
}


void Professor::edit_grade(const int& enrollmentId, const int& grade)
{
	try
	{
		Database::session() << "UPDATE enrollments SET grade = :grade WHERE enrollment_id = :enrollmentId",
			soci::use(grade), soci::use(enrollmentId);
	}
	catch (const std::exception& err)
	{
		throw std::runtime_error(std::string("Error Editing Grade: ") + err.what());
	}
}
