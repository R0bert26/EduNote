#ifndef ROUTER_H
#define ROUTER_H


#include <crow.h>
#include <vector>
#include <string>


class Router
{
public:
	void init_routes(crow::SimpleApp& app);
};


#endif
