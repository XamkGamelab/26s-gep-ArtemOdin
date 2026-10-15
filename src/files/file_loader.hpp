#pragma once

#include <string>

namespace gep::file
{
    class file_loader
    {
    public:
        static auto FileContent(const std::string& path) -> std::string;
    };
}