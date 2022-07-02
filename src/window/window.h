#pragma once
#include <iostream>

#include "camera.h"
#include "../shaders/shader.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#define MAX_KEYS 1024
#define MAX_BUTTONS 32

static bool m_keys[MAX_KEYS];
static bool m_mouseButtons[MAX_BUTTONS];
static double mx, my;
static float m_lastX;
static float m_lastY;
static bool m_firstMouse = true;
static Camera m_camera;

namespace photosynthesis {
	namespace graphics {
		class Window {
		public:
			float deltaTime = 0.0f;
			float lastFrame = 0.0f;
			Shader* m_shader;
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
				m_lastX = m_width / 2.0f;
				m_lastY = m_height / 2.0f;
				m_shader = new Shader("src/shaders/vertex.vert", "src/shaders/fragment.frag");
			}
			void clear() {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
			void update() {
				float currentFrame = static_cast<float>(glfwGetTime());
				deltaTime = currentFrame - lastFrame;
				lastFrame = currentFrame;
				glfwPollEvents();
				glfwGetFramebufferSize(m_window, &m_width, &m_height);
				glfwSwapBuffers(m_window);
			}
			void useShader() {
				m_shader->enable();
			}
			bool isKeyPressed(unsigned int keycode) {
				//tdo log system
				if (keycode >= MAX_KEYS) return false;
				return m_keys[keycode];
			}
			bool isMouseButtonPressed(unsigned int mouse) {
				if (mouse >= MAX_BUTTONS) return false;
				return m_mouseButtons[mouse];
			}
			void getMousePosition(double& x, double& y) {
				x = mx;
				y = my;
			}
			bool closed() {
				return glfwWindowShouldClose(m_window);
			}
			void close() {
				glfwSetWindowShouldClose(m_window, GL_TRUE);
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
			float m_deltaTime = 0.0f;	// time between current frame and last frame
			float m_lastFrame = 0.0f;
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
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				glfwMakeContextCurrent(m_window);
				glfwSetWindowSizeCallback(m_window, resize_window);
				glfwSetKeyCallback(m_window, key_callback);
				glfwSetMouseButtonCallback(m_window, mouse_button_callback);
				glfwSetCursorPosCallback(m_window, mouse_callback);
				glfwSetScrollCallback(m_window, scroll_callback);
				if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
					std::cout << "Failed to initialize GLAD!" << std::endl;
					return false;
				}
				glViewport(0, 0, m_width, m_height);
				glEnable(GL_DEPTH_TEST);
				m_camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
				return true;
			}
			 static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
				m_keys[key] = action != GLFW_RELEASE;
			 }
			 static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
				 m_mouseButtons[button] = action != GLFW_RELEASE;
			 }
			 static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
				 float xpos = static_cast<float>(xposIn);
				 float ypos = static_cast<float>(yposIn);
				
				 mx = xpos;
				 my = ypos;

				 if (m_firstMouse)
				 {
					 m_lastX = xpos;
					 m_lastY = ypos;
					 m_firstMouse = false;
				 }

				 float xoffset = xpos - m_lastX;
				 float yoffset = m_lastY - ypos; // reversed since y-coordinates go from bottom to top

				 m_lastX = xpos;
				 m_lastY = ypos;

				 m_camera.ProcessMouseMovement(xoffset, yoffset);
			 }

			 static void resize_window(GLFWwindow* window, int width, int height) {
				 glViewport(0, 0, width, height);
			 }
			 static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
			 {
				 m_camera.ProcessMouseScroll(static_cast<float>(yoffset));
			 }
		};
	}
}
