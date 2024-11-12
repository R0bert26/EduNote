#include "error.h"
#include "view.h"

void Error::generate_error_page(crow::response& res, const int& errorCode, const std::string& errorMessage)
{
	crow::mustache::context ctx;

	ctx["error_code"] = std::to_string(errorCode);
	ctx["error_message"] = errorMessage;

	auto page = crow::mustache::load("error.html");

	res.code = errorCode;
	res.body = page.render_string(ctx);
}