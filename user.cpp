#include "user.h"

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