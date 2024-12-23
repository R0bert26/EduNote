#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H


#include <crow.h>
#include "../model/admin.h"


class AdminController
{
public:
	static void run(crow::response& res, const crow::request& req);

private:
	static void add_user(crow::response& res, crow::json::rvalue& data, Admin& admin);
	static void delete_user(crow::response& res, crow::json::rvalue& data, Admin& admin);
	static void logout(crow::response& res);
};


#endif
