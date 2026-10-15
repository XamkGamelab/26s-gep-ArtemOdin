#include "file_loader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

auto gep::file::file_loader::FileContent(const std::string& path) -> std::string
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}