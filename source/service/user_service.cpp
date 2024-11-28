#include <iostream>
#include <string>
#include "../../headers/service/user_service.h"
#include "../../headers/service/hashing_service.h"


bool UserService::check_auth(const std::string& email, const std::string& password)
{
	std::string hashedPassword;

	Database::session() << "SELECT password FROM users WHERE email = :email",
		soci::into(hashedPassword), soci::use(email);

	return HashingService::verify_password(password, hashedPassword);
}


User UserService::get_user(const std::string& email)
{
	int id = 0;
	std::string firstName = "";
	std::string lastName = "";
	std::string role = "";

	Database::session() << "SELECT id, first_name, last_name, role FROM users WHERE email = :email",
		soci::into(id), soci::into(firstName), soci::into(lastName), soci::into(role), soci::use(email);

	if (id == 0 || firstName == "" || lastName == "" || role == "")
	{
		return User(0, "", "", "", "");
	}

	return User(id, firstName, lastName, email, role);
}
