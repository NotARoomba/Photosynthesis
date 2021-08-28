#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

namespace photosynthesis {
	namespace graphics {
		class Window {
		public:
			Window(const char *title, int width, int height) {
				//Stores title, width and height of window
				m_title = title;
				m_width = width;
				m_height = height;
				if (!init()) {
					glfwTerminate();
				}
			}
			void clean() {
				
			}
			void update() {
				glfwPollEvents();
				glfwGetFramebufferSize(m_window, &m_width, &m_height);
				glfwSwapBuffers(m_window);
			}
			bool closed() {
				return glfwWindowShouldClose(m_window);
			}
			~Window() {
				glfwTerminate();
			}
		private:
			GLFWwindow* m_window;
			const char *m_title;
			int m_width, m_height;
			//Initialize the window
			bool init() {
				if (!glfwInit()) {
					std::cout << "Failed to initialize GLFW!" << std::endl;
					return false;
				}
				m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
				if (!m_window) {
					std::cout << "Failed to create the GLFW window!" << std::endl;
					return false;
				}
				glfwMakeContextCurrent(m_window);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
				return true;
			}
		};
	}
}