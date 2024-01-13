

#include "person.h"
#include <string_view>



Person::Person(std::string_view name, std::string_view surname) :
    name(name),
    surname(surname) {}

Person::~Person() = default;

std::string_view Person::get_name() const noexcept {
    return name;
}

std::string_view Person::get_surname() const noexcept {
    return surname;
}

bool Person::operator== (const Person& other) const noexcept = default;

std::strong_ordering Person::operator<=>(const Person& other) const noexcept {
    if (auto cmp = surname <=> other.surname; cmp != 0)
        return cmp;
    return name <=> other.name;
}