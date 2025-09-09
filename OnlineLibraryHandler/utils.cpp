#include "Utils.h"

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool clearFailedExtraction()
{
    if (!std::cin)
    {
        if (std::cin.eof())
        {
            std::exit(0);
        }

        std::cin.clear();
        ignoreLine();

        return true;
    }

    return false;
}

bool readNonEmptyLine(const std::string& prompt, std::string& out) {
    std::cout << prompt;
    if (!std::getline(std::cin, out)) return false;
    if (out.empty() || std::all_of(out.begin(), out.end(),
        [](unsigned char c) { 
            return std::isspace(c); 
        })) {
        std::cerr << "Input cannot be empty or whitespace only.\n";
        return false;
    }
    return true;
}

bool readCharOption(const std::string& prompt, const std::string& validOptions, char& out) {
    std::cout << prompt;
    if (!(std::cin >> out)) return false;
    ignoreLine();
    if (validOptions.find(out) == std::string::npos) {
        std::cerr << "Invalid option. Valid options: " << validOptions << "\n";
        return false;
    }
    return true;
}

