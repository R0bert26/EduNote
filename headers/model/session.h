#ifndef SESSION_H
#define SESSION_H


#include "user.h"


class Session
{
public:
	static void create_session(const User& user);
	static void logout();
	static User get_current_session();

private:
	static User currentUser;
};


#endif
