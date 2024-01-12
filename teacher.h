#pragma once

#include "person.h"
#include "course.h"
#include "college_utils.h"
#include <set>
#include <memory>

class College;

class Teacher: public virtual Person{
    std::set<std::shared_ptr<Course>, college_utils::SharedComp> courses;

    friend class College;

public:
    Teacher(std::string_view name, std::string_view surname);

    const std::set<std::shared_ptr<Course>, college_utils::SharedComp>& get_courses() const;
};