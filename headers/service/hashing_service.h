#ifndef HASHINGSERVICE_H
#define HASHINGSERVICE_H


#include <string>
#include <sodium.h>


class HashingService
{
public:
	static std::string hash_password(const std::string& password);
	static bool verify_password(const std::string& password, const std::string& hashedPassword);
};


#endif
