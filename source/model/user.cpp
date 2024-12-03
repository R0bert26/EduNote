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


bool User::add_user(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password, const std::string& role)
{
	int status = 0;
	std::string hashedPassword = HashingService::hash_password(password);

	Database::session() << "INSERT INTO users (email, password, role, first_name, last_name) VALUES (:email, :hashedPassword, :role, :firstName, :lastName)",
		soci::use(email), soci::use(hashedPassword), soci::use(role), soci::use(firstName), soci::use(lastName);

	Database::session() << "SELECT COUNT(*) FROM users WHERE email = :email",
		soci::into(status), soci::use(email);

	return status != 0;
}


bool User::delete_user(const std::string& email)
{
	int status = 1;

	Database::session() << "DELETE FROM users WHERE email = :email",
		soci::use(email);

	Database::session() << "SELECT COUNT(*) FROM users WHERE email = :email",
		soci::into(status), soci::use(email);

	return status == 0;
}
