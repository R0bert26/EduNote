#ifndef USERSERVICE_H
#define USERSERVICE_H


#include <string>
#include "../model/user.h"


class UserService
{
public:
	static bool check_auth(const std::string& email, const std::string& password);

	static User get_user(const std::string& email);
};


#endif
