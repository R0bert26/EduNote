#include "user_service.h"
#include <iostream>

bool UserService::check_auth(const std::string& email, const std::string& password)
{
	int id = 0;

	DataBase::session() << "SELECT id FROM users WHERE email = :email AND password = :password",
		soci::into(id), soci::use(email), soci::use(password);

	return (id != 0);
}

User UserService::get_user(const std::string& email, const std::string& password)
{
	int id = 0;
	std::string firstName = "";
	std::string lastName = "";
	std::string role = "";

	DataBase::session() << "SELECT id, first_name, last_name, role FROM users WHERE email = :email AND password = :password",
		soci::into(id), soci::into(firstName), soci::into(lastName), soci::into(role), soci::use(email), soci::use(password);

	if (id == 0 || firstName == "" || lastName == "" || role == "")
	{
		std::cerr << "\nError Getting User\n" << std::endl;

		return User(0, "", "", "", "");
	}

	return User(id, firstName, lastName, email, role);
}