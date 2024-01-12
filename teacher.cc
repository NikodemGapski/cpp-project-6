#include "teacher.h"
#include "course.h"

Teacher::Teacher(std::string_view name, std::string_view surname) :
    Person(name, surname) {}

const std::set<std::shared_ptr<Course>, college_utils::SharedComp>& Teacher::get_courses() const {
    return courses;
}
