#ifndef PROFESSORCONTROLLER_H
#define PROFESSORCONTROLLER_H


#include <crow.h>
#include "../model/professor.h"


class ProfessorController
{
public:
	static void run(crow::response& res, const crow::request& req);

private:
	static void add_course(crow::response& res, crow::json::rvalue& data, Professor& professor);

	static void get_courses(crow::response& res, crow::json::rvalue& data, Professor& professor);

	static void delete_course(crow::response& res, crow::json::rvalue& data, Professor& professor);

	static void add_student(crow::response& res, crow::json::rvalue& data, Professor& professor);

	static void get_enrollments(crow::response& res, crow::json::rvalue& data, Professor& professor);

	static void delete_enrollment(crow::response& res, crow::json::rvalue& data, Professor& professor);

	static void logout(crow::response& res);
};


#endif
