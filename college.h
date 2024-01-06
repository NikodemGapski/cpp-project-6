#pragma once
#include "person.h"
#include "student.h"
#include "teacher.h"
#include "phdstudent.h"
#include "course.h"
#include "college_utils.h"

#include <type_traits> // std::is_same_v
#include <unordered_set>
#include <set>
#include <vector>
#include <string>

class College {

	template <typename T>
	using ptr = const std::shared_ptr<T>&;
	template <typename T>
	using uset_ptr = std::unordered_set<ptr<T>>;
	template <typename T>
	using set_ptr = std::set<ptr<T>>;

	using people_t = uset_ptr<Person>;
	using students_t = uset_ptr<Student>;
	using teachers_t = uset_ptr<Teacher>;
	using phd_students_t = uset_ptr<PhDStudent>;
	using courses_t = uset_ptr<Course>;

public:
	bool add_course(std::string_view name, bool active = true) {return false;}

    auto find_courses(std::string_view pattern) {
		set_ptr<Course> res;
		for (const auto& p : courses) {
			if (college_utils::is_match(pattern, p->get_name()))
				res.insert(p);
		}
		return res;
	}

    bool change_course_activeness(ptr<Course> course, bool active) {return false;}

    bool remove_course(ptr<Course> course) {return false;}

    bool change_student_activeness(ptr<Student> student, bool active) {return false;}

    template<college_utils::StudTeach T>
    set_ptr<T> find(ptr<Course> course) {
		if constexpr (std::is_same_v<T, Student>) {
			return find_in<T>(students, course);
		} else {
			return find_in<T>(teachers, course);
		}
	}

    template <college_utils::StudTeach T>
    bool assign_course(ptr<T> person, ptr<Course> course) {return false;}

	template <college_utils::SpecialPerson T>
	bool add_person(std::string_view name, std::string_view surname, bool active = true) {
		// Check if such person exists in the database.
		if (find<Person>(name, surname).size() > 0)
			return false;
		// If not, create one and add them to the database.
		insert_person<T>(create_person<T>(name, surname, active));
		return true;
	}

	template <college_utils::PersonBased T>
	set_ptr<T> find(std::string_view name_pattern, std::string_view surname_pattern) const {
		if constexpr (std::is_same_v<T, Student>) {
			return find_in<T>(students, name_pattern, surname_pattern);
		}
		if constexpr (std::is_same_v<T, Teacher>) {
			return find_in<T>(teachers, name_pattern, surname_pattern);
		}
		if constexpr (std::is_same_v<T, PhDStudent>) {
			return find_in<T>(phd_students, name_pattern, surname_pattern);
		}
		if constexpr (std::is_same_v<T, Person>) {
			return find_in<T>(people, name_pattern, surname_pattern);
		}
	}

private:
	people_t people;
	students_t students;
	teachers_t teachers;
	phd_students_t phd_students;
    courses_t courses;

	template <college_utils::SpecialPerson T>
	set_ptr<T> create_person(std::string_view name, std::string_view surname, bool active) {
		if constexpr (std::is_same_v<T, Teacher>) {
			return std::make_shared<T>(name, surname);
		} else {
			return std::make_shared<T>(name, surname, active);
		}
	}

	template <college_utils::SpecialPerson T>
	void insert_person(ptr<T> person) {
		people.insert(person);
		if constexpr (std::is_base_of_v<Student, T>) {
			students.insert(person);
		}
		if constexpr (std::is_base_of_v<Teacher, T>) {
			teachers.insert(person);
		}
		if constexpr (std::is_same_v<T, PhDStudent>) {
			phd_students.insert(person);
		}
	}

	template <college_utils::PersonBased T, typename C>
	set_ptr<T> find_in(const C& container, std::string_view name_pattern, std::string_view surname_pattern) const {
		set_ptr<T> res;
		for (const auto& p : container) {
			if (
				college_utils::is_match(name_pattern, p->get_name()) &&
				college_utils::is_match(surname_pattern, p->get_surname())
			)
				res.insert(p);
		}
		return res;
	}

	template <college_utils::StudTeach T, typename C>
	set_ptr<T> find_in(const C& container, ptr<Course> course) {
		set_ptr<T> res;
		for (const auto& p : container) {
			if (p->get_courses().contains(course))
				res.insert(p);
		}
		return res;
	}
};