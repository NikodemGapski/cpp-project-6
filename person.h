#pragma once
#include <string>


class Person {
    std::string surname;
    std::string name;

public:

    Person(std::string_view name, std::string_view surname);

    virtual ~Person();

    std::string_view get_name() const;

    std::string_view get_surname() const;

    bool operator== (const Person& other) const;

    std::strong_ordering operator<=> (const Person& other) const;

};