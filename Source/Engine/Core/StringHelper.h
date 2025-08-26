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

	inline bool compare(const std::string& str1, const std::string& str2) {
		if (str1.length() != str2.length()) return false;

		return std::equal(str1.begin(), str1.end(),str2.begin(), [](char a, char b){
			return (std::tolower(a) == std::tolower(b));
			});
	}
}