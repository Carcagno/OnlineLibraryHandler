#pragma once

#include <cstdlib>
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>

void ignoreLine();
bool clearFailedExtraction();
bool readNonEmptyLine(const std::string& prompt, std::string& out);
bool readCharOption(const std::string& prompt, const std::string& validOptions, char& out);


// case for double/ int/ etc.
// maybe use a .tpp in the future to avoid implem in .h ?
template<typename T>
bool readValue(const std::string& prompt, T& out) {
	std::string line;
	std::cout << prompt;
	if (!std::getline(std::cin, line) || line.empty()) {
		ignoreLine();
		return false;
	}
	std::istringstream iss(line);
	return bool(iss >> out);
}