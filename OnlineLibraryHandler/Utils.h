#pragma once

#include <cstdlib>
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <string>

void ignoreLine();
bool clearFailedExtraction();
bool readNonEmptyLine(const std::string& prompt, std::string& out);
bool readCharOption(const std::string& prompt, const std::string& validOptions, char& out);