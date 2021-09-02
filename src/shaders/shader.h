#pragma once
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include "../utils/fileUtils.h"

namespace photosynthesis {
	namespace graphics {
		class Shader {
		public:
			Shader(const char* vertPath, const char* fragPath) : m_vertPath(vertPath), m_fragPath(fragPath) {
				const char* vertSrc = read_file(vertPath).c_str();
				const char* fragSrc = read_file(fragPath).c_str();
				m_ShaderID = load(vertSrc, fragSrc);
			}
			void enable() {
				glUseProgram(m_ShaderID);
			}
			void disable() {
				glUseProgram(0);
			}
		private:
			GLuint m_ShaderID;
			const char* m_vertPath;
			const char* m_fragPath;
			GLuint load(const char* vertSrc, const char* fragSrc) {
				GLuint program = glCreateProgram();
				GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
				GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

				glShaderSource(vertex, 1, &vertSrc, NULL);
				glCompileShader(vertex);

				GLint result;
				glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
				if (result == GL_FALSE) {
					GLint length;
					glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
					std::vector<char> error(length);
					glGetShaderInfoLog(vertex, length, &length, &error[0]);
					glDeleteShader(vertex);
					return 0;
				}

				glShaderSource(fragment, 1, &fragSrc, NULL);
				glCompileShader(fragment);

				glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
				if (result == GL_FALSE) {
					GLint length;
					glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
					std::vector<char> error(length);
					glGetShaderInfoLog(fragment, length, &length, &error[0]);
					glDeleteShader(fragment);
					return 0;
				}

				glAttachShader(program, vertex);
				glAttachShader(program, fragment);

				glLinkProgram(program);
				glValidateProgram(program);

				glDeleteShader(vertex);
				glDeleteShader(fragment);

				return program;
			}
		};
	}
}