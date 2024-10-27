#ifndef ROUTER_H
#define ROUTER_H

#include <crow.h>

class Router
{
public:
	void init_routes(crow::SimpleApp& app);
};

#endif