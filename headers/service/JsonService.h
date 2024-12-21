#ifndef JSONSERVICE_H
#define JSONSERVICE_H


#include <crow.h>


class JsonService
{
public:
	static void create_error_response(crow::response& res, const std::string& status, const std::string& message, const int& code);
};


#endif
