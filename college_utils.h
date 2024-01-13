#pragma once

#include "forward_declarations.h"

#include <string>
#include <string_view>
#include <regex>
#include <concepts> // std::same_as
#include <set>
#include <memory>

/* A set of general-purpose utility functions. */
namespace college_utils {
	/* Concepts */

	/* Student or Teacher. */
	template <typename T>
	concept StudTeach =
		std::same_as<T, Student> ||
		std::same_as<T, Teacher>;

	/* Student, Teacher, or PhDStudent. */
	template <typename T>
	concept SpecialPerson =
		StudTeach<T> ||
		std::same_as<T, PhDStudent>;
	
	/* Derived from Person. */
	template <typename T>
	concept PersonBased = std::derived_from<T, Person>;

	/* Has a constructor accepting (std::string_view, std::string_view, bool) */
	template <typename T>
	concept HasActivityConstructor =
		std::constructible_from<T, std::string_view, std::string_view, bool>;

	/* Has an is_active() method returning a boolean. */
	template <typename T>
	concept HasActivity = requires(T a) {
		{a.is_active()} -> std::same_as<bool>;
	};

	/* Shared pointer comparator based on the pointed objects. */
	struct SharedComp {
		template <typename T>
		bool operator()(const std::shared_ptr<T>& a,
						const std::shared_ptr<T>& b) const {
			return (*a) < (*b);
		}
	};
	
	/* A std::set of shared pointers of T with the special comparator. */
	template <typename T>
	using set_ptr = std::set<std::shared_ptr<T>, SharedComp>;

	/* Regular expressions matcher. */
	inline bool is_match(std::string_view pattern, std::string_view text) {
		// Transform the pattern to match the ECMAScript grammar.
		static std::string special_chars = "\\.[{()<>*+-=!?^$|";
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
}