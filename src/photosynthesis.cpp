#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shaders/shader.h"
#include "camera.h"
#include "photosynthesis.h"


bool Photosynthesis::keys[MAX_KEYS];
bool Photosynthesis::mouseButtons[MAX_BUTTONS];
double Photosynthesis::mx, Photosynthesis::my;
float Photosynthesis::m_lastX;
float Photosynthesis::m_lastY;
bool Photosynthesis::m_firstMouse;
Camera *Photosynthesis::camera;
float Photosynthesis::deltaTime;

Photosynthesis::Photosynthesis(int sx, int sy, std::string name, glm::vec3 color, const char* vertPath, const char* fragPath) {
	this->width = sx;
	this->height = sy;
	this->name = name;
	this->color = color;
	Photosynthesis::m_firstMouse = true;
	if (init(sx, sy) == -1) return;
	shader = new Shader("src/shaders/vertex.vert", "src/shaders/fragment.frag");
}
void Photosynthesis::update() {
    static float lastFrame = 0.0f;
    float currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    this->fps = 1.0f / deltaTime; // Calculate frames per second

    glfwPollEvents();
}
bool Photosynthesis::shouldClose() {return glfwWindowShouldClose(window);};
void Photosynthesis::useShader() {
	shader->enable();
}
void Photosynthesis::swap() {
	glfwSwapBuffers(window);
}
int Photosynthesis::getWidth() {return width;};
int Photosynthesis::getHeight() { return height;};
void Photosynthesis::clear() {
	glClearColor(this->color.x, this->color.y, this->color.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
bool Photosynthesis::isKeyPressed(unsigned int keycode) {
	//tdo log system
	if (keycode >= MAX_KEYS) return false;
	return Photosynthesis::keys[keycode];
}
bool Photosynthesis::isMouseButtonPressed(unsigned int mouse) {
	if (mouse >= MAX_BUTTONS) return false;
	return Photosynthesis::mouseButtons[mouse];
}
void Photosynthesis::getMousePosition(double& x, double& y) {
	x = Photosynthesis::mx;
	y = Photosynthesis::my;
}
void Photosynthesis::setCamera(Camera * cam) {
	Photosynthesis::camera = cam;
}
glm::vec3 Photosynthesis::viewToWorldCoordTransform(int s_x, int s_y) {
    // NORMALISED DEVICE SPACE
    double x = 2.0 * s_x / this->width - 1;
    double y = 2.0 * s_y / this->height - 1;
    // HOMOGENEOUS SPACE
    glm::vec4 screenPos = glm::vec4(x, -y, -1.0f, 1.0f);
    // Projection/Eye Space
    glm::mat4 ProjectView = glm::mat4(1.0f) * glm::mat4(1.0f);
    glm::mat4 viewProjectionInverse = inverse(ProjectView);
    glm::vec4 worldPos = viewProjectionInverse * screenPos;
    return glm::vec3(worldPos);
}
void Photosynthesis::close() {
	glfwSetWindowShouldClose(window, GL_TRUE);
}
Photosynthesis::~Photosynthesis() {
	glfwTerminate();
}
void Photosynthesis::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
} 
int Photosynthesis::init(int sx, int sy) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	window = glfwCreateWindow(sx, sy, this->name.c_str(), NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}	    
	glViewport(0, 0, sx, sy);
	glfwSetFramebufferSizeCallback(window, Photosynthesis::framebuffer_size_callback); 
	glfwSetKeyCallback(window, Photosynthesis::key_callback);
	glfwSetMouseButtonCallback(window, Photosynthesis::mouse_button_callback);
	// glfwSetCursorPosCallback(window, mouse_callback);
	// glfwSetScrollCallback(window, scroll_callback);
	return 0;
}
void Photosynthesis::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Photosynthesis::keys[key] = action != GLFW_RELEASE;
}
void Photosynthesis::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	Photosynthesis::mouseButtons[button] = action != GLFW_RELEASE;
}
void Photosynthesis::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	Photosynthesis::mx = xpos;
	Photosynthesis::my = ypos;

	if (Photosynthesis::m_firstMouse)
	{
		Photosynthesis::m_lastX = xpos;
		Photosynthesis::m_lastY = ypos;
		Photosynthesis::m_firstMouse = false;
	}

	float xoffset = xpos - Photosynthesis::m_lastX;
	float yoffset = Photosynthesis::m_lastY - ypos; // reversed since y-coordinates go from bottom to top

	Photosynthesis::m_lastX = xpos;
	Photosynthesis::m_lastY = ypos;

	Photosynthesis::camera->ProcessMouseMovement(xoffset, yoffset);
}
void Photosynthesis::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Photosynthesis::camera->ProcessMouseScroll(static_cast<float>(yoffset));
}
