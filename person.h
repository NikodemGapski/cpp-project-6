#pragma once
#include <string>
#include <string_view>

class Person {
    std::string name;
    std::string surname;

public:

    Person() = delete;
    Person(const Person&) = delete;

    Person(std::string_view name, std::string_view surname);

    virtual ~Person();

    std::string_view get_name() const noexcept;

    std::string_view get_surname() const noexcept;

    bool operator== (const Person& other) const noexcept;

    std::strong_ordering operator<=> (const Person& other) const noexcept;

};