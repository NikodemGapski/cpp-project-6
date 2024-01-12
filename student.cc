#include "student.h"


Student::Student(std::string_view name, std::string_view surname, bool active) :
    Person(name, surname),
    active(active) {}

bool Student::is_active() const {
    return active;
}

const college_utils::set_ptr<Course>& Student::get_courses() const {
    return courses;
}
