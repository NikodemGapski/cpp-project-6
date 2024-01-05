#pragma once
#include "course.h"
#include "person.h"
#include "phdstudent.h"
#include "student.h"
#include "student.h"
#include "teacher.h"
#include <set>
#include <unordered_set>
#include <string>
#include <string_view>


class College {


    std::set<Course> courses;
    std::unordered_set<Person> people;

public:
    bool add_course(std::string_view name, bool active = true);

    auto find_courses(std::string_view pattern); //???

    bool change_course_activeness(Course& course, bool active);

    bool remove_course(Course& course);

    template<typename T>
    bool add_person(std::string_view name, std::string_view surname, bool active = true);

    bool change_student_activeness(Student& student, bool active);

    template <typename T>
    auto find(std::string_view name_pattern, std::string_view surname_pattern); //???

    template<typename T>
    auto find(Course& course);

    template <typename T>
    bool assign_course(T& person, Course& student);
};