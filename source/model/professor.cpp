#include "../../headers/model/professor.h"
#include "../../headers/model/student.h"
#include "../../headers/model/enrollment.h"


Professor::Professor(
	const int id,
	const std::string& firstName,
	const std::string& lastName,
	const std::string& email,
	const std::string& role) :
	User(id, firstName, lastName, email, role) {}


bool Professor::add_course(const std::string& courseName)
{
	try
	{
		soci::statement st = (Database::session().prepare << "INSERT INTO courses (course_name, professor_id) VALUES (:courseName, :professorId)",
			soci::use(courseName), soci::use(this->get_id()));

		st.execute();

		return true;
	}
	catch (const soci::soci_error)
	{
		return false;
	}
}


bool Professor::delete_course(const int& courseId)
{
	try
	{
		soci::statement st = (Database::session().prepare << "DELETE FROM courses WHERE course_id = :courseId", 
			soci::use(courseId));

		st.execute();

		return true;
	}
	catch (const soci::soci_error)
	{
		return false;
	}
}


bool Professor::add_enrollments(const std::string& studentEmail, const int& courseId)
{
	User user = User::get_user(studentEmail);
	if (user.get_id() == 0 || user.get_role() != "student")
	{
		return false;
	}

	auto status = Enrollment::add_enrollment(user.get_id(), courseId);
	if (!status)
	{
		return false;
	}

	return true;
}

bool Professor::delete_enrollment(int enrollmentId)
{
	try
	{
		Database::session() << "DELETE FROM enrollments WHERE enrollment_id = :enrollmentId",
			soci::use(enrollmentId);

		return true;
	}
	catch (const soci::soci_error)
	{
		return false;
	}
}
