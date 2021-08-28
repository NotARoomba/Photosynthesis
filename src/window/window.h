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
			void clear() {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
			void update() {
				glfwPollEvents();
				glfwGetFramebufferSize(m_window, &m_width, &m_height);
				glfwSwapBuffers(m_window);
			}
			bool closed() {
				return glfwWindowShouldClose(m_window);
			}
			inline int getWidth() { return m_width; }
			inline int getHeight() { return m_height; }
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
				glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
					glViewport(0, 0, width, height);
					});
				return true;
			}
		};
	}
}
