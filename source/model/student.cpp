#include "../../headers/model/student.h"


Student::Student(
	const int id,
	const std::string& firstName,
	const std::string& lastName,
	const std::string& email,
	const std::string& role) :
	User(id, firstName, lastName, email, role) {}


std::string Student::get_full_name(const int& id)
{
	try
	{
		std::string firstName;
		std::string lastName;

		Database::session() << "SELECT first_name, last_name FROM users WHERE user_id = :id",
			soci::into(firstName), soci::into(lastName), soci::use(id);

		std::string fullName = firstName + " " + lastName;

		return fullName;
	}
	catch (const std::exception& err)
	{
		throw std::runtime_error(std::string("Error Getting Student Name: ") + err.what());
	}
}


std::vector<Enrollment> Student::get_enrollments()
{
	try
	{
		std::vector<Enrollment> enrollments;

		soci::rowset<soci::row> rs = (Database::session().prepare << "SELECT * FROM enrollments WHERE student_id = :studentId",
			soci::use(this->get_id()));

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
