#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shaders/shader.cpp"

#define STB_IMAGE_IMPLEMENTATION

class Photosynthesis {
public:
	Shader* shader;
	Photosynthesis(int sx, int sy) {
		if (init(sx, sy) == -1) return;
		shader = new Shader("src/shaders/vertex.vert", "src/shaders/fragment.frag");
	}
	void update() {
	    glfwSwapBuffers(window);
	    glfwPollEvents();    
	}
	bool shouldClose() {return glfwWindowShouldClose(window);};
	void useShader() {
		shader->enable();
	}
	void clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	 	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
	 	return 0;
	}
};