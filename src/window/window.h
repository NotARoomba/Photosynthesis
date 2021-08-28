#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace photosynthesis {
	namespace graphics {
		class Window {
		public:
			Window(const char* title, int width, int height) {
				//Stores title, width and height of window
				m_title = title;
				m_width = width;
				m_height = height;
				if (!init()) {
					glfwTerminate();
				}
				for (int i = 0; i < MAX_KEYS; i++) {
					m_keys[i] = false;
				}
				for (int i = 0; i < MAX_BUTTONS; i++) {
					m_mouseButtons[i] = false;
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
			bool isKeyPressed(unsigned int keycode) {
				//tdo log system
				if (keycode >= MAX_KEYS) return false;
				return m_keys[keycode];
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
			const char* m_title;
			int m_width, m_height;
			static bool m_keys[MAX_KEYS];
			static bool m_mouseButtons[MAX_BUTTONS];
			double mx, my;
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
				glfwSetKeyCallback(m_window, key_callback);
				if (glewInit() != GLEW_OK) {
					std::cout << "Failed to initialize GLEW!" << std::endl;
					return false;
				}
				return true;
			}
			 static inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
				m_keys[key] = action != GLFW_RELEASE;
			}
		};
	}
}
