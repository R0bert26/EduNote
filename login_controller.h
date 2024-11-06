#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <crow.h>

class LoginController
{
public:
	void login(const crow::request& req, crow::response& res);
};

#endif