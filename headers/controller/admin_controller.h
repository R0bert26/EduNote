#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H


#include <crow.h>


class AdminController
{
public:
	static void run(crow::response& res, const crow::request& req);
};


#endif
