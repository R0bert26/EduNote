#ifndef PROFESSOR_H
#define PROFESSOR_H


#include "user.h"


class Professor : public User
{
public:
	Professor(
		const int& id,
		const std::string& firstName,
		const std::string& lastName,
		const std::string& email,
		const std::string& role);

	void add_course(const std::string& courseName);
	void delete_course(const int& courseId);
	void add_enrollment(const std::string& studentEmail, const int& courseId);
	void delete_enrollment(const int& enrollmentId);
	void edit_grade(const int& enrollmentId, const int& grade);
};


#endif
