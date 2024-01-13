#include "course.h"

Course::Course(std::string_view name, bool active) :
    name(name),
    active(active) {}

std::string_view Course::get_name() const noexcept {
    return name;
}

bool Course::is_active() const noexcept {
    return active;
}

std::strong_ordering Course::operator<=>(const Course& other) const noexcept {
    return name <=> other.name;
}
