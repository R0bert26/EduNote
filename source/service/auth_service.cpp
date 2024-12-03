#include <iostream>
#include <string>
#include "../../headers/service/auth_service.h"
#include "../../headers/service/hashing_service.h"
#include "../../headers/app/database.h"


bool AuthService::check_auth(const std::string& email, const std::string& password)
{
	std::string hashedPassword;

	Database::session() << "SELECT password FROM users WHERE email = :email",
		soci::into(hashedPassword), soci::use(email);

	return HashingService::verify_password(password, hashedPassword);
}
