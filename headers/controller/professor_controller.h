#ifndef PROFESSORCONTROLLER_H
#define PROFESSORCONTROLLER_H


#include <crow.h>


class ProfessorController
{
public:
	static void run(crow::response& res, const crow::request& req);
};


#endif
