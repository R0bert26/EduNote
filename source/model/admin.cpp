#include "../../headers/model/admin.h"
#include "../../headers/service/hashing_service.h"
#include "../../headers/app/database.h"


Admin::Admin(
	const int id,
	const std::string& firstName,
	const std::string& lastName,
	const std::string& email,
	const std::string& role) :
	User(id, firstName, lastName, email, role) {}


void Admin::add_user(
	const std::string& firstName,
	const std::string& lastName,
	const std::string& email,
	const std::string& password,
	const std::string& role)
{
	try
	{
		std::string hashedPassword = HashingService::hash_password(password);

		Database::session() << "INSERT INTO users (email, password, role, first_name, last_name) VALUES (:email, :hashedPassword, :role, :firstName, :lastName)",
			soci::use(email), soci::use(hashedPassword), soci::use(role), soci::use(firstName), soci::use(lastName);
	}
	catch (const std::exception& err)
	{
		throw std::runtime_error(std::string("Error Adding User: ") + err.what());
	}
}


void Admin::delete_user(const std::string& email)
{
	try
	{
		int userCount = 0;

		Database::session() << "SELECT COUNT(*) FROM users WHERE email = :email",
			soci::use(email), soci::into(userCount);

		if (userCount == 0)
		{
			throw std::runtime_error("User Does Not Exist.");
		}

		Database::session() << "DELETE FROM users WHERE email = :email",
			soci::use(email);
	}
	catch (const std::exception& err)
	{
		throw std::runtime_error(std::string("Error Deleting User: ") + err.what());
	}
}
