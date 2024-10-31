#include <iostream>
#include <crow.h>
#include "data_base.h"
#include "router.h"

int main()
{
	crow::SimpleApp app;
	Router router;

	try
	{
		DataBase::connect();

		std::cout << "Database connected" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Database connection error: " << e.what() << std::endl;

		return 1;
	}

	router.init_routes(app);

	app.port(18080).multithreaded().run();

	return 0;
}