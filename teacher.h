#pragma once

#include "person.h"
#include "course.h"
#include <set>


class Teacher: public virtual Person{
    std::set<Course> courses;

public:
    Teacher(std::string_view name, std::string_view surname);

    const std::set<Course>& get_courses() const;
};