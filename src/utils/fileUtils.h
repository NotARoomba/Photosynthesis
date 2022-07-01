#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace photosynthesis {
	const char* read_file(const char* filepath) {
        std::string code;
        std::ifstream file;
        // ensure ifstream objects can throw exceptions:
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            file.open(filepath);
            std::stringstream stream;
            // read file's buffer contents into streams
            stream << file.rdbuf();
            // close file handlers
            file.close();
            // convert stream into string
            code = stream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
		return code.c_str();
	}
}