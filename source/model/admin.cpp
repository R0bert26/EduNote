#include "../../headers/model/admin.h"
#include "../../headers/service/hashing_service.h"
#include "../../headers/app/database.h"


Admin::Admin(
	const int id,
	const std::string& firstName,
	const std::string& lastName,
	const std::string& email,
	const std::string& role) :
	User(id, firstName, lastName, email, role)
{}


bool Admin::add_user(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password, const std::string& role)
{
	int status = 0;
	std::string hashedPassword = HashingService::hash_password(password);

	Database::session() << "INSERT INTO users (email, password, role, first_name, last_name) VALUES (:email, :hashedPassword, :role, :firstName, :lastName)",
		soci::use(email), soci::use(hashedPassword), soci::use(role), soci::use(firstName), soci::use(lastName);

	Database::session() << "SELECT COUNT(*) FROM users WHERE email = :email",
		soci::into(status), soci::use(email);

	return status != 0;
}


bool Admin::delete_user(const std::string& email)
{
	int status = 1;

	Database::session() << "DELETE FROM users WHERE email = :email",
		soci::use(email);

	Database::session() << "SELECT COUNT(*) FROM users WHERE email = :email",
		soci::into(status), soci::use(email);

	return status == 0;
}
