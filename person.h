#pragma once
#include <string>

class Person {
public:
	Person(std::string a, std::string b) : a(a), b(b) {}
	virtual std::string get_name() {
		return a;
	}
	virtual std::string get_surname() {
		return b;
	}
private:
	std::string a, b;
};