#include <iostream>
#include <crow.h>
#include "data_base.h"
#include "router.h"

int main()
{
	try
	{
		DataBase::connect();

		std::cout << "Database Connected" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Database Connection Error: " << e.what() << std::endl;

		return 1;
	}

	crow::SimpleApp app;
	Router router;

	crow::mustache::set_global_base("./");

	router.init_routes(app);

	std::cout << "Server started on port 18080\n" << std::endl;

	app.port(18080).multithreaded().run();

	return 0;
}