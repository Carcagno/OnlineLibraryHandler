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