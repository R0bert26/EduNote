#include "../../headers/model/course.h"
#include "../../headers/app/database.h"


Course::Course(const int& id, const std::string& name, const int& user_id) :
	id(id),
	name(name),
	professor_id(user_id) {}


int Course::get_id()
{
	return this->id;
}


std::string Course::get_name()
{
	return this->name;
}


int Course::get_professor_id()
{
	return this->professor_id;
}


std::vector<Course> Course::get_courses(const int& professorId)
{
	std::vector<Course> courses;

	soci::rowset<soci::row> rs = (Database::session().prepare << "SELECT * FROM courses WHERE professor_id = :professorId",
		soci::use(professorId));

	for (auto& row : rs)
	{
		Course course(row.get<int>("course_id"), row.get<std::string>("course_name"), row.get<int>("professor_id"));
		courses.emplace_back(course);
	}

	return courses;
}

std::string Course::get_course_name(const int& id)
{
	std::string name;

	try
	{
		Database::session() << "SELECT course_name FROM courses WHERE course_id = :id",
			soci::into(name), soci::use(id);

		return name;
	}
	catch (soci::soci_error& e)
	{
		return "";
	}
}
