#pragma once

#include "person.h"
#include "course.h"
#include <set>
#include <memory>


class Teacher: public virtual Person{
    std::set<std::shared_ptr<Course>> courses;

public:
    Teacher(std::string_view name, std::string_view surname);

    const std::set<std::shared_ptr<Course>>& get_courses() const;
};