#pragma once
#include <string>

namespace bacon {
	inline std::string ToLower(const std::string& str) {
		std::string result = str;

		for (char& c : result) {
			c = std::tolower(c);
		}
		return result;
	}

	inline std::string ToUpper(const std::string& str) {
		std::string result = str;

		for (char& c : result) {
			c = std::toupper(c);
		}
		return result;
	}
}