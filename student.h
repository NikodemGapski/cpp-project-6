#pragma once

#include "person.h"
#include "course.h"
#include <string_view>
#include <set>
#include <memory>


class Student : public virtual Person {

    bool active;
    std::set<std::shared_ptr<Course>> courses;

public:
    Student(std::string_view name, std::string_view surname, bool active = true);

    bool is_active() const;

    const std::set<std::shared_ptr<Course>>& get_courses() const;
};