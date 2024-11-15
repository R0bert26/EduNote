#include "../../headers/app/database.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::unique_ptr<Database> Database::instance = nullptr;

Database::Database(
	const std::string& dbName,
	const std::string& user,
	const std::string& password,
	const std::string& host,
	const std::string& port) :
	sql(soci::postgresql, "dbname=" + dbName + " user=" + user + " password=" + password + " host=" + host + " port=" + port) {}

std::unordered_map<std::string, std::string> Database::getParams()
{
	std::unordered_map<std::string, std::string> params;
	std::string key;
	std::string value;
	std::string line;

	std::ifstream file(".env");

	if (!file.is_open())
	{
		std::cerr << "Error opening .env file" << std::endl;

		exit(1);
	}

	while (getline(file, line))
	{
		std::stringstream ss(line);

		getline(ss, key, '=');
		getline(ss, value, '=');

		params[key] = value;
	}

	return params;
}

soci::session& Database::session()
{
	if (!instance)
	{
		std::cerr << "Database not connected" << std::endl;

		exit(1);
	}

	return instance->sql;
}

void Database::connect()
{
	if (!instance)
	{
		std::unordered_map<std::string, std::string> params = Database::getParams();

		if (params.find("DB_NAME") == params.end() ||
			params.find("DB_USER") == params.end() ||
			params.find("DB_PASSWORD") == params.end() ||
			params.find("DB_HOST") == params.end() ||
			params.find("DB_PORT") == params.end())
		{
			std::cerr << "Error configuring database" << std::endl;

			exit(1);
		}

		instance = std::unique_ptr<Database>(new Database(params["DB_NAME"], params["DB_USER"], params["DB_PASSWORD"], params["DB_HOST"], params["DB_PORT"]));
	}
}