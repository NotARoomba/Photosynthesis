#pragma once
#include <string>

class FileUtils {
    public:
        static std::string read_file(const char* filepath);
        static unsigned int loadTexture(char const* path);
};