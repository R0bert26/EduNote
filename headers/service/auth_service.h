#ifndef USERSERVICE_H
#define USERSERVICE_H


#include <string>


class AuthService
{
public:
	static bool check_auth(const std::string& email, const std::string& password);
};


#endif
