#include "phdstudent.h"

PhDStudent::PhDStudent(std::string_view name, std::string_view surname, bool active):
    Person(name, surname),
    Student(name, surname, active),
    Teacher(name, surname) {}
