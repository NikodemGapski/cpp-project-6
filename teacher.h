#pragma once

#include "person.h"
#include "course.h"
#include "college_utils.h"
#include <set>
#include <memory>

class College;

class Teacher: public virtual Person{
    college_utils::set_ptr<Course> courses;

    friend class College;

public:
    Teacher(std::string_view name, std::string_view surname);

    const college_utils::set_ptr<Course>& get_courses() const;
};