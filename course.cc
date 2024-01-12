#include "course.h"

Course::Course(std::string_view name, bool active) :
    name(name),
    active(active) {}

std::string_view Course::get_name() const {
    return name;
}

bool Course::is_active() const {
    return active;
}

std::strong_ordering Course::operator<=>(const Course& other) const {
    return name <=> other.name;
}
