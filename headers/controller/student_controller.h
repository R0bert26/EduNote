#ifndef STUDENTCONTROLLER_H
#define STUDENTCONTROLLER_H


#include <crow.h>
#include "../model/student.h"


class StudentController
{
public:
	static void run(crow::response& res, const crow::request& req);

private:
	static void get_student_enrollments(crow::response& res, crow::json::rvalue& data, Student& student);
	static void logout(crow::response& res);
};


#endif
