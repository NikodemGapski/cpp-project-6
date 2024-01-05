#include "phdstudent.h"

PhDStudent::PhDStudent(std::string_view name, std::string_view surname, bool active):
    Student(name, surname, active),
    Teacher(name, surname),
    Person(name, surname) {}
