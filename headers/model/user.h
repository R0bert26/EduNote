#ifndef USER_H
#define USER_H


#include <string>
#include "../app/database.h"


class User
{
public:
	User(
		const int id,
		const std::string& firstName,
		const std::string& lastName,
		const std::string& email,
		const std::string& role);

	int get_id();

	std::string get_email();

	std::string get_role();

	std::string get_first_name();

	std::string get_last_name();

	static User get_user(const std::string& email);

	virtual ~User();

private:
	int id;

	std::string firstName;

	std::string lastName;

	std::string email;

	std::string role;
};


#endif
