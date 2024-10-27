#include "login_controller.h"

crow::response LoginController::render()
{
	return loginView.render();
}