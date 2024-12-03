#ifndef STUDENTCONTROLLER_H
#define STUDENTCONTROLLER_H


#include <crow.h>


class StudentController
{
public:
	static void run(crow::response& res, const crow::request& req);
};


#endif
