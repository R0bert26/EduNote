#include "data_base.h"
#include <fstream>
#include <iostream>

std::unique_ptr<DataBase> DataBase::instance = nullptr;

DataBase::DataBase(
	const std::string& dbName,
	const std::string& user,
	const std::string& password,
	const std::string& host,
	const std::string& port) : sql(soci::postgresql,
		"dbname=" + dbName + " user=" + user + " password=" + password + " host=" + host + " port=" + port) {}

std::unordered_map<std::string, std::string> DataBase::getParams()
{
	std::unordered_map<std::string, std::string> params;
	std::string key;
	std::string value;

	std::ifstream file("config.txt");

	if (!file)
	{
		std::cerr << "Error opening config.txt" << std::endl;

		exit(1);
	}

	while (file >> key >> value)
	{
		key.pop_back();

		params[key] = value;
	}

	return params;
}

soci::session& DataBase::session()
{
	if (!instance)
	{
		std::cerr << "Database not connected" << std::endl;
	}

	return instance->sql;
}

void DataBase::connect()
{
	if (!instance)
	{
		std::unordered_map<std::string, std::string> params = DataBase::getParams();

		if (params.find("dbName") == params.end() ||
			params.find("user") == params.end() ||
			params.find("password") == params.end() ||
			params.find("host") == params.end() ||
			params.find("port") == params.end())
		{
			std::cerr << "Error configuring database" << std::endl;

			return;
		}

		instance = std::unique_ptr<DataBase>(new DataBase(params["dbName"], params["user"], params["password"], params["host"], params["port"]));
	}
}