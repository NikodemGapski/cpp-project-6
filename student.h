#pragma once

class Student : public virtual Person {
public:
	Student(std::string a, std::string b, bool active) : Person(a, b) {}
};