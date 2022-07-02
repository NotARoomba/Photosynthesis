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
				m_ShaderID = load(read_file(vertPath), read_file(fragPath));
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
			void setVec3(const std::string& name, glm::vec3 value) const
			{
				glUniform3fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, glm::value_ptr(value));
			}
		private:
			int m_ShaderID;
			const char* m_vertPath;
			const char* m_fragPath;
			int load(std::string vertCode, std::string fragCode) {
				const char* vertSrc = vertCode.c_str();
				const char* fragSrc = fragCode.c_str();
				unsigned int vertex, fragment;
				int success;
				char infoLog[512];
				// vertex Shader
				vertex = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(vertex, 1, &vertSrc, NULL);
				glCompileShader(vertex);
				
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
				
				glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(fragment, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
				};
				// shader Program
				int ID = glCreateProgram();
				glAttachShader(ID, vertex);
				glAttachShader(ID, fragment);
				glLinkProgram(ID);
				
				glGetProgramiv(ID, GL_LINK_STATUS, &success);
				if (!success)
				{
					glGetProgramInfoLog(ID, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
				}

				glDeleteShader(vertex);
				glDeleteShader(fragment);

				return ID;
			}
		};
	}
}