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
	using ptr = std::shared_ptr<T>;
	template <typename T>
	using uset_ptr = std::unordered_set<ptr<T>>;
	using people_t = uset_ptr<Person>;
	using students_t = uset_ptr<Student>;
	using teachers_t = uset_ptr<Teacher>;
	using phd_students_t = uset_ptr<PhDStudent>;
public:
	bool add_course(std::string_view name, bool active = true);

    auto find_courses(std::string_view pattern); //???

    bool change_course_activeness(Course& course, bool active);

    bool remove_course(Course& course);

    bool change_student_activeness(Student& student, bool active);

    template<typename T>
    auto find(Course& course);

    template <typename T>
    bool assign_course(T& person, Course& student);

	template <college_utils::SpecialPerson T>
	bool add_person(const std::string& name, const std::string& surname, bool active = true) {
		// Check if such person exists in the database.
		if (find<Person>(name, surname).size() > 0)
			return false;
		// If not, create one and add them to the database.
		insert_person<T>(create_person<T>(name, surname, active));
		return true;
	}

	template <college_utils::PersonBased T>
	std::vector<ptr<T>> find(const std::string& name_pattern, const std::string& surname_pattern) const {
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
    std::set<Course> courses;

	template <college_utils::SpecialPerson T>
	auto create_person(const std::string& name, const std::string& surname, bool active) {
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
	std::vector<ptr<T>> find_in(const C& container, const std::string& name_pattern, const std::string& surname_pattern) const {
		std::vector<ptr<T>> res;
		for (const auto& p : container) {
			if (
				college_utils::is_match(name_pattern, p->get_name()) &&
				college_utils::is_match(surname_pattern, p->get_surname())
			)
				res.push_back(p);
		}
		return res;
	}
};