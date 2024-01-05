#pragma once

#include "person.h"
#include "course.h"
#include <string_view>
#include <set>


class Student : public virtual Person {

    bool active;
    std::set<Course> courses;

public:
    Student(std::string_view name, std::string_view surname, bool active = true);

    bool is_active() const;

    const std::set<Course>& get_courses() const;
};