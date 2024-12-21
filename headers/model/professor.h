#ifndef PROFESSOR_H
#define PROFESSOR_H


#include "user.h"


class Professor : public User
{
public:
	Professor(
		const int id,
		const std::string& firstName,
		const std::string& lastName,
		const std::string& email,
		const std::string& role
	);

	bool add_course(const std::string& courseName);

	bool delete_course(const int& courseId);

	bool add_enrollments(const std::string& studentEmail, const int& courseId);

	bool delete_enrollment(int enrollmentId);
};


#endif
