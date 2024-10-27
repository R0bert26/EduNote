#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <crow.h>
#include "login_view.h"

class LoginController
{
public:
	crow::response render();

private:
	LoginView loginView;
};

#endif