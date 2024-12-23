#ifndef ENROLLMENT_H
#define ENROLLMENT_H


#include <vector>


class Enrollment
{
public:
	Enrollment(const int& id, const int& studentId, const int& courseId, const int& grade);
	static void add_enrollment(const int& studentId, const int& courseId);
	static std::vector<Enrollment> get_course_enrollments(const int& courseId);
	int get_id();
	int get_student_id();
	int get_course_id();
	int get_grade();

private:
	int id;
	int studentId;
	int courseId;
	int grade;
};


#endif
