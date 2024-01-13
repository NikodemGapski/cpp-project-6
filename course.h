#pragma once

#include <string>
#include <string_view>

class College;

class Course {
    std::string name;
    bool active;

    friend class College;

public:

    Course(std::string_view name, bool active = true);

    std::string_view get_name() const noexcept;

    bool is_active() const noexcept;

    std::strong_ordering operator<=> (const Course& other) const noexcept;
};