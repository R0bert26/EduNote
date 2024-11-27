#include "../../headers//model/session.h"


User Session::currentUser = User(0, "", "", "", "");


void Session::create_session(const User& user)
{
	currentUser = user;
}


void Session::logout()
{
	currentUser = User(0, "", "", "", "");

	// TODO: implement logout
}


User Session::get_current_session()
{
	return currentUser;
}
