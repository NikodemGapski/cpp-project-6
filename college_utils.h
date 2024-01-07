#pragma once
#include "person.h"
#include "student.h"
#include "teacher.h"
#include "phdstudent.h"

#include <string>
#include <regex>
#include <type_traits> // std::is_same_v

/* A set of general-purpose utility functions. */
namespace college_utils {
	/* Concepts */
	template <typename T>
	concept StudTeach =
		std::is_same_v<T, Student> ||
		std::is_same_v<T, Teacher>;

	template <typename T>
	concept SpecialPerson =
		StudTeach<T> ||
		std::is_same_v<T, PhDStudent>;
	
	template <typename T>
	concept PersonBased = std::is_base_of_v<Person, T>;

	template <typename T>
	concept HasActivity = requires(T a) {
		{a.is_active()} -> std::same_as<bool>;
	};

	/* Regular expressions */
	bool is_match(std::string_view pattern, std::string_view text) {
		// Transform the pattern to match the ECMAScript grammar.
		std::string ecma = "^";
		for (char c : pattern) {
			if (c == '?') {
				ecma.push_back('.');
			} else if (c == '*') {
				ecma.append({'.', '*'});
			} else {
				ecma.push_back(c);
			}
		}
		ecma.push_back('$');
		std::regex rgx(ecma);
		return std::regex_match(std::string{text}, rgx);
	}
}