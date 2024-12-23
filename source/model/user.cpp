#include "../../headers/model/user.h"
#include "../../headers/app/database.h"
#include "../../headers/service/hashing_service.h"


User::User(
	const int id,
	const std::string& firstName,
	const std::string& lastName,
	const std::string& email,
	const std::string& role) :
	id(id), firstName(firstName), lastName(lastName), email(email), role(role) {}


int User::get_id()
{
	return this->id;
}


std::string User::get_email()
{
	return this->email;
}


std::string User::get_role()
{
	return this->role;
}


std::string User::get_first_name()
{
	return this->firstName;
}


std::string User::get_last_name()
{
	return this->lastName;
}


User User::get_user(const std::string& email)
{
	try
	{
		int userID = 0;
		std::string firstName = "";
		std::string lastName = "";
		std::string role = "";

		Database::session() << "SELECT user_id, first_name, last_name, role FROM users WHERE email = :email",
			soci::into(userID), soci::into(firstName), soci::into(lastName), soci::into(role), soci::use(email);

		if (userID == 0 || firstName == "" || lastName == "" || role == "")
		{
			throw std::runtime_error("User Not Found");
		}

		return User(userID, firstName, lastName, email, role);
	}
	catch (const std::exception& err)
	{
		throw std::runtime_error(std::string("Error Getting User: ") + err.what());
	}
}


User::~User() {}
