#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H


#include <crow.h>


class LoginController
{
public:
	static void login(const crow::request& req, crow::response& res);
};


#endif
