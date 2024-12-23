#ifndef STUDENT_H
#define STUDENT_H


#include "user.h"
#include <vector>
#include "enrollment.h"


class Student : public User
{
public:
	Student(
		const int id,
		const std::string& firstName,
		const std::string& lastName,
		const std::string& email,
		const std::string& role);

	static std::string get_full_name(const int& id);
	std::vector<Enrollment> get_enrollments();
};


#endif
