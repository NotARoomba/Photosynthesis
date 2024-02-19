#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shaders/shader.h"
#include "camera.h"

#define STB_IMAGE_IMPLEMENTATION
#define MAX_KEYS 1024
#define MAX_BUTTONS 32

class Photosynthesis {
public:


	static bool keys[MAX_KEYS];
	static bool mouseButtons[MAX_BUTTONS];
	static double mx, my;
	static float m_lastX;
	static float m_lastY;
	static bool m_firstMouse;
	static Camera *camera;
	static float deltaTime;

	Shader* shader;
	float lastFrame = 0.0f;
	int width,height;
	std::string name;
	glm::vec3 color;
	int fps;
	Photosynthesis(int sx, int sy, std::string name, glm::vec3 color, const char* vertPath, const char* fragPath);
	void update();
	bool shouldClose();
	void useShader();
	void swap();
	int getWidth();
	int getHeight();
	void clear();
	bool isKeyPressed(unsigned int keycode);
	bool isMouseButtonPressed(unsigned int mouse);
	void getMousePosition(double& x, double& y);
	void setCamera(Camera * cam);
	glm::vec3 viewToWorldCoordTransform(int x, int y);
	void close();
	~Photosynthesis();
private:
	GLFWwindow* window;


	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	int init(int sx, int sy);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static float getDeltaTime();
};