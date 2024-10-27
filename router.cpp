#include "router.h"
#include "login_controller.h"

void Router::init_routes(crow::SimpleApp& app)
{
	LoginController loginController;

	CROW_ROUTE(app, "/")([&loginController]()
		{
			return loginController.render();
		});
}