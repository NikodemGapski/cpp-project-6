#pragma once

class PhDStudent : public Student, public Teacher {
public:
	PhDStudent(std::string a, std::string b, bool active)
	: Person(a, b), Student(a, b, active), Teacher(a, b) {}
};