#pragma once

#include "student.h"
#include "teacher.h"

class PhDStudent : public Student, public Teacher {

public:
    PhDStudent() = delete;
    PhDStudent(const PhDStudent&) = delete;

    PhDStudent(std::string_view name, std::string_view surname, bool active = true);
};