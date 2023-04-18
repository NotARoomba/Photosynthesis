#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shaders/shader.cpp"
#include "camera.cpp"

#define STB_IMAGE_IMPLEMENTATION
#define MAX_KEYS 1024
#define MAX_BUTTONS 32

static bool keys[MAX_KEYS];
static bool mouseButtons[MAX_BUTTONS];
static double mx, my;
static float m_lastX;
static float m_lastY;
static bool m_firstMouse = true;
static Camera camera;


class Photosynthesis {
public:
	Shader* shader;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	int width,height;
	Photosynthesis(int sx, int sy) {
		this->width = sx;
		this->height = sy;
		if (init(sx, sy) == -1) return;
		shader = new Shader("src/shaders/vertex.vert", "src/shaders/fragment.frag");
	}
	void update() {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	    glfwPollEvents();    
	}
	bool shouldClose() {return glfwWindowShouldClose(window);};
	void useShader() {
		shader->enable();
	}
	void swap() {
	    glfwSwapBuffers(window);
	}
	int getWidth() {return width;};
	int getHeight() { return height;};
	void clear() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	bool isKeyPressed(unsigned int keycode) {
		//tdo log system
		if (keycode >= MAX_KEYS) return false;
		return keys[keycode];
	}
	bool isMouseButtonPressed(unsigned int mouse) {
		if (mouse >= MAX_BUTTONS) return false;
		return mouseButtons[mouse];
	}
	void getMousePosition(double& x, double& y) {
		x = mx;
		y = my;
	}
	void close() {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	~Photosynthesis() {
		glfwTerminate();
	}
private:
	GLFWwindow* window;


	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	    glViewport(0, 0, width, height);
	} 
	int init(int sx, int sy) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		window = glfwCreateWindow(sx, sy, "Photosynthesis", NULL, NULL);
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
		camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	 	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		// glfwSetCursorPosCallback(window, mouse_callback);
		// glfwSetScrollCallback(window, scroll_callback);
	 	return 0;
	}
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		keys[key] = action != GLFW_RELEASE;
	}
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		mouseButtons[button] = action != GLFW_RELEASE;
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

		camera.ProcessMouseMovement(xoffset, yoffset);
	}
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		camera.ProcessMouseScroll(static_cast<float>(yoffset));
	}
};