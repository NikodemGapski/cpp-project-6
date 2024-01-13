#include "teacher.h"
#include "course.h"

Teacher::Teacher(std::string_view name, std::string_view surname) :
    Person(name, surname) {}

const college_utils::set_ptr<Course>& Teacher::get_courses() const noexcept {
    return courses;
}
