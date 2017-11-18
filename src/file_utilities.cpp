#include "file_utilities.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::string FileUtilities::LoadFile(const char* path)
{
    std::ifstream file(path);
    std::stringstream string_stream;

    if (file.is_open() == false)
    {
        std::cerr << "Failed to open file: " << path << '\n';

        return "";
    }

    string_stream << file.rdbuf();

    return string_stream.str();
}
