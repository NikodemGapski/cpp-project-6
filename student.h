#pragma once

#include "person.h"
#include "course.h"
#include "college_utils.h"
#include <string_view>
#include <set>
#include <memory>

class College;

class Student : public virtual Person {
    bool active;
    college_utils::set_ptr<Course> courses;

    friend class College;

public:
    Student(std::string_view name, std::string_view surname, bool active = true);

    bool is_active() const;

    const college_utils::set_ptr<Course>& get_courses() const;
};