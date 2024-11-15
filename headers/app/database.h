#ifndef DATABASE_H
#define DATABASE_H

#include <soci/soci.h>
#include <soci/postgresql/soci-postgresql.h>
#include <string>
#include <unordered_map>

class Database
{
public:
	static soci::session& session();

	static void connect();

private:
	static std::unique_ptr<Database> instance;

	Database(
		const std::string& dbName,
		const std::string& user,
		const std::string& password,
		const std::string& host,
		const std::string& port);

	soci::session sql;

	static std::unordered_map<std::string, std::string> getParams();
};

#endif