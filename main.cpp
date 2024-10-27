#include <iostream>
#include <crow.h>
#include "router.h"

int main()
{
	crow::SimpleApp app;
	Router router;

	router.init_routes(app);

	app.port(18080).multithreaded().run();
}