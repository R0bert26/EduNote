#ifndef ERROR_H
#define ERROR_H


#include <crow.h>
#include <string>


class Error
{
public:
	static void generate_error_page(crow::response& res, const int& errorCode, const std::string& errorMessage);
};


#endif
