#pragma once
#include <string>
#include <string_view>
class Course {

    std::string name;
    bool active;

public:

    Course(std::string_view name, bool active = true);

    std::string_view get_name() const;

    bool is_active() const;

    std::strong_ordering operator<=> (const Course& other) const;
};