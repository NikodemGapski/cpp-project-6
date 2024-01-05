#include "student.h"


Student::Student(std::string_view name, std::string_view surname, bool active) :
    active(active),
    Person(name, surname) {}

bool Student::is_active() const {
    return active;
}

const std::set<Course> &Student::get_courses() const {
    return courses;
}
