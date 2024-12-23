#include "../../headers/model/enrollment.h"
#include "../../headers/app/database.h"


Enrollment::Enrollment(const int& id, const int& studentId, const int& courseId, const int& grade) :
	id(id),
	studentId(studentId),
	courseId(courseId),
	grade(grade) {}


void Enrollment::add_enrollment(const int& studentId, const int& courseId)
{
	try
	{
		Database::session() << "INSERT INTO enrollments (course_id, student_id) VALUES (:courseId, :studentId)",
			soci::use(courseId), soci::use(studentId);
	}
	catch (const std::exception& err)
	{
		throw std::runtime_error(std::string("Error Adding Enrollment: ") + err.what());
	}
}


std::vector<Enrollment> Enrollment::get_course_enrollments(const int& courseId)
{
	try
	{
		soci::rowset<soci::row> rs = (Database::session().prepare << "SELECT * FROM enrollments WHERE course_id = :courseId",
			soci::use(courseId));

		std::vector<Enrollment> enrollments;
		for (auto& row : rs)
		{
			Enrollment enrollment(
				row.get<int>("enrollment_id"),
				row.get<int>("student_id"),
				row.get<int>("course_id"),
				row.get<int>("grade"));

			enrollments.emplace_back(enrollment);
		}

		return enrollments;
	}
	catch (const std::exception& err)
	{
		throw std::runtime_error(std::string("Error Getting Enrollments: ") + err.what());
	}
}


int Enrollment::get_id()
{
	return this->id;
}


int Enrollment::get_student_id()
{
	return this->studentId;
}


int Enrollment::get_course_id()
{
	return this->courseId;
}


int Enrollment::get_grade()
{
	return this->grade;
}
