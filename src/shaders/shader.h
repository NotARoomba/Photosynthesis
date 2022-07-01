#pragma once
#include <vector>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "../utils/fileUtils.h"

namespace photosynthesis {
	namespace graphics {
		class Shader {
		public:
			Shader(const char* vertPath, const char* fragPath) : m_vertPath(vertPath), m_fragPath(fragPath) {
				const char* vertSrc = read_file(vertPath);
				const char* fragSrc = read_file(fragPath);
				m_ShaderID = load(vertSrc, fragSrc);
			}
			void enable() {
				glUseProgram(m_ShaderID);
			}
			void disable() {
				glUseProgram(0);
			}
			void setBool(const std::string& name, bool value) const
			{
				glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), (int)value);
			}
			void setInt(const std::string& name, int value) const
			{
				glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), value);
			}
			void setFloat(const std::string& name, float value) const
			{
				glUniform1f(glGetUniformLocation(m_ShaderID, name.c_str()), value);
			}
			void setMat4(const std::string& name, glm::mat4 value) const
			{
				glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
			}
		private:
			GLuint m_ShaderID;
			const char* m_vertPath;
			const char* m_fragPath;
			GLuint load(const char* vertSrc, const char* fragSrc) {
				unsigned int vertex, fragment;
				int success;
				char infoLog[512];
				// vertex Shader
				vertex = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(vertex, 1, &vertSrc, NULL);
				glCompileShader(vertex);
				// print compile errors if any
				glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(vertex, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
				};
				//fragment shader
				fragment = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(fragment, 1, &fragSrc, NULL);
				glCompileShader(fragment);
				// print compile errors if any
				glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(fragment, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
				};
				// shader Program
				GLuint ID = glCreateProgram();
				glAttachShader(ID, vertex);
				glAttachShader(ID, fragment);
				glLinkProgram(ID);
				// print linking errors if any
				glGetProgramiv(ID, GL_LINK_STATUS, &success);
				if (!success)
				{
					glGetProgramInfoLog(ID, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
				}

				// delete the shaders as they're linked into our program now and no longer necessary
				glDeleteShader(vertex);
				glDeleteShader(fragment);

				return ID;
			}
		};
	}
}