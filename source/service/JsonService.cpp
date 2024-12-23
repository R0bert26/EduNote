#include "../../headers/service/JsonService.h"


void JsonService::create_error_response(crow::response& res, const std::string& status, const std::string& message, const int& code)
{
	crow::json::wvalue response;
	response["status"] = status;
	response["message"] = message;

	res.set_header("Content-Type", "application/json");
	res.code = code;
	res.write(response.dump());
	res.end();
}
