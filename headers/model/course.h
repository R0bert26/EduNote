#ifndef COURSE_H
#define COURSE_H


#include <string>
#include <vector>

class Course
{
public:
	Course(const int& id, const std::string& name, const int& user_id);

	int get_id();

	std::string get_name();

	int get_professor_id();

	static std::vector<Course> get_courses(const int& professor_id);

	static std::string get_course_name(const int& id);

private:
	int id;
	std::string name;
	int professor_id;
};


#endif
