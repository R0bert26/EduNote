#ifndef ADMIN_H
#define ADMIN_H


#include "user.h"
#include <vector>


class Admin : public User
{
public:
	Admin(
		const int id,
		const std::string& firstName,
		const std::string& lastName,
		const std::string& email,
		const std::string& role);

	static bool add_user(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password, const std::string& role);

	static bool delete_user(const std::string& email);
};


#endif
