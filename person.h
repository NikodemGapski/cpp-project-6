#pragma once
#include <string>


class Person {
    std::string name;
    std::string surname;

public:

    Person(std::string_view name, std::string_view surname);

    virtual ~Person();

    std::string_view get_name() const;

    std::string_view get_surname() const;

    bool operator== (const Person& other) const;

};