

#include "person.h"
#include <string_view>



Person::Person(std::string_view name, std::string_view surname) :
    name(name),
    surname(surname) {}

Person::~Person() = default;

std::string_view Person::get_name() const {
    return name;
}

std::string_view Person::get_surname() const {
    return surname;
}

bool Person::operator== (const Person& other) const = default;