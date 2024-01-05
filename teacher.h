#pragma once

class Teacher : public virtual Person {
public:
	Teacher(std::string a, std::string b) : Person(a, b) {}
};