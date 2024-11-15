#include <iostream>
#include <crow.h>
#include "headers/app/database.h"
#include "headers/app/router.h"

int main()
{
	try
	{
		Database::connect();

		std::cout << "Database connected" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Database connection error: " << e.what() << std::endl;

		return 1;
	}

	crow::SimpleApp app;
	Router router;
	const int port = 18080;

	crow::mustache::set_global_base("resources/templates");

	router.init_routes(app);

	std::cout << "Server started on port " << port << "\n" << std::endl;

	app.port(port).multithreaded().run();

	return 0;
}