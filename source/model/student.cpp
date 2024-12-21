#include "../../headers/model/student.h"


Student::Student(
	const int id,
	const std::string& firstName,
	const std::string& lastName,
	const std::string& email,
	const std::string& role) :
	User(id, firstName, lastName, email, role) {}


std::string Student::get_full_name(int id)
{
	std::string firstName;
	std::string lastName;

	try
	{
		Database::session() << "SELECT first_name, last_name FROM users WHERE user_id = :id",
			soci::into(firstName), soci::into(lastName), soci::use(id);

		std::string fullName = firstName + " " + lastName;

		return fullName;
	}
	catch (soci::soci_error& e)
	{
		return "";
	}
}
