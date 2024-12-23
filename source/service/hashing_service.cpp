#include <stdexcept>
#include "../../headers/service/hashing_service.h"


std::string HashingService::hash_password(const std::string& password)
{
	char hashedPassword[crypto_pwhash_STRBYTES];

	auto ok = crypto_pwhash_str(hashedPassword,
		password.c_str(),
		password.size(),
		crypto_pwhash_OPSLIMIT_INTERACTIVE,
		crypto_pwhash_MEMLIMIT_INTERACTIVE);

	if (ok != 0)
	{
		throw std::runtime_error("Failed to hash password");
	}

	return std::string(hashedPassword);
}


bool HashingService::verify_password(const std::string& password, const std::string& hashedPassword)
{
	return crypto_pwhash_str_verify(hashedPassword.c_str(), password.c_str(), password.size()) == 0;
}
