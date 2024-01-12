#pragma once
#include "person.h"
#include "student.h"
#include "teacher.h"
#include "phdstudent.h"
#include "course.h"
#include "college_utils.h"

#include <type_traits> // std::is_same_v
#include <unordered_set> // data indexing
#include <set> // find results
#include <string_view> // std::string_view

#define TODO throw std::runtime_error("Not implemented");

class College {
	template <typename T>
	using ptr = std::shared_ptr<T>;
	template <typename T>
	using uset_ptr = std::unordered_set<ptr<T>>;
	template <typename T>
	using set_ptr = college_utils::set_ptr<T>;

	using people_t = uset_ptr<Person>;
	using courses_t = uset_ptr<Course>;

public:
    const set_ptr<Course> find_courses(std::string_view pattern) const {
		set_ptr<Course> res;
		for (const auto& p : courses) {
			if (college_utils::is_match(pattern, p->get_name()))
				res.insert(p);
		}
		return res;
	}

	bool add_course(std::string_view name, bool active = true) {
		if (!find_courses(name).empty())
			return false;
		courses.insert(std::make_shared<Course>(name, active));
		return true;
	}

    bool change_course_activeness(ptr<Course> course, bool active) {
		if (!courses.contains(course))
			return false;
		course->active = active;
		return true;
	}

    bool remove_course(ptr<Course> course) {
		if (!courses.contains(course))
			return false;
		course->active = false;
		courses.erase(course);
		return true;
	}

    bool change_student_activeness(ptr<Student> student, bool active) {
        if (!people.contains(student))
            return false;
		student->active = active;
        return true;
	}

    template<college_utils::StudTeach T>
    const set_ptr<T> find(ptr<Course> course) const {
		set_ptr<T> res;
		for (const auto& p : people) {
			auto casted = cast<T>(p);
			if (casted && casted->get_courses().contains(course))
				res.insert(casted);
		}
		return res;
	}

    template <college_utils::StudTeach T>
    bool assign_course(ptr<T> person, ptr<Course> course) {
		check(course);
		check(person);

		if (person->get_courses().contains(course))
			return false;
		person->courses.insert(course);
        return true;
	}

	template <college_utils::SpecialPerson T>
	bool add_person(std::string_view name, std::string_view surname, bool active = true) {
		// Check if such person exists in the database.
		if (!find<Person>(name, surname).empty())
			return false;
		// If not, create one and add them to the database.
		people.insert(create_person<T>(name, surname, active));
		return true;
	}

	template <college_utils::PersonBased T>
	const set_ptr<T> find(std::string_view name_pattern, std::string_view surname_pattern) const {
		set_ptr<T> res;
		for (const auto& p : people) {
			if (cast<T>(p) &&
				college_utils::is_match(name_pattern, p->get_name()) &&
				college_utils::is_match(surname_pattern, p->get_surname()))
				res.insert(cast<T>(p));
		}
		return res;
	}

private:
	people_t people;
    courses_t courses;

	template <college_utils::SpecialPerson T>
	ptr<T> create_person(std::string_view name, std::string_view surname, bool active) const {
		if constexpr (std::is_same_v<T, Teacher>) {
			return std::make_shared<T>(name, surname);
		} else {
			return std::make_shared<T>(name, surname, active);
		}
	}

	void check(ptr<Course> course) const {
		if (!courses.contains(course))
			throw std::invalid_argument("Non-existing course.");
		if (!course->is_active())
			throw std::invalid_argument("Incorrect operation on an inactive course.");
	}

	template <college_utils::StudTeach T>
	void check(ptr<T> person) const {
		if (!people.contains(person))
			throw std::invalid_argument("Non-existing person.");
		if constexpr (std::same_as<T, Student>) {
			if (!person->is_active())
				throw std::invalid_argument("Incorrect operation for an inactive student.");
		}
	}

	template <typename T, typename Arg>
	ptr<T> cast(ptr<Arg> arg) const {
		return std::dynamic_pointer_cast<T>(arg);
	}
};