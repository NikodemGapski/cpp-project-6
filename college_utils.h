#pragma once
#include "person.h"
#include "student.h"
#include "teacher.h"
#include "phdstudent.h"

#include <string>
#include <string_view>
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
		static std::string special_chars = ".^$+()[{\\|";
		std::string ecma = "^";
		for (char c : pattern) {
			if (c == '?') {
				ecma.push_back('.');
			} else if (c == '*') {
				ecma.append({'.', '*'});
			} else if (special_chars.find(c) != std::string::npos) {
				ecma.append({'\\', c});
			} else {
				ecma.push_back(c);
			}
		}
		ecma.push_back('$');
		std::regex rgx(ecma);
		return std::regex_match(std::string{text}, rgx);
	}

	/* Shared pointer comparator */
	struct SharedComp {
		template <typename T>
		bool operator()(const std::shared_ptr<T>& a,
						const std::shared_ptr<T>& b) const {
			return (*a) < (*b);
		}
	};
}