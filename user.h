#ifndef USER_H
#define USER_H

#include "data_base.h"
#include <string>

class User
{
public:
	User(const int id,
		const std::string& firstName,
		const std::string& lastName,
		const std::string& email,
		const std::string& role);

	int get_id();

	std::string get_email();

	std::string get_role();

	std::string get_first_name();

	std::string get_last_name();

private:
	int id;
	std::string firstName;
	std::string lastName;
	std::string email;
	std::string role;
};

#endif