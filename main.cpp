#include "src/window/window.h"
#include "src/utils/fileUtils.h"
#include "src/shaders/shader.h"
#include "src/utils/drawUtils.h"
#include <iostream>


using namespace photosynthesis;
using namespace graphics;
using namespace items;

int main() {
	Window window("Photosynthesis Engine", 960, 540);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	srand(time(NULL));
	for (int i = 0; i < 1; i++) {
		//addItem(new Triangle(
		//	glm::vec3(
		//		(float)rand() / (float)RAND_MAX * 10.0f - 5.0f,
		//		(float)rand() / (float)RAND_MAX * 10.0f - 5.0f,
		//		(float)rand() / (float)RAND_MAX * 10.0f - 5.0f
		//	),
		//	glm::vec3(
		//		(float)rand() / (float)RAND_MAX * 10.0f - 5.0f,
		//		(float)rand() / (float)RAND_MAX * 10.0f - 5.0f,
		//		(float)rand() / (float)RAND_MAX * 10.0f - 5.0f
		//	),
		//	glm::vec3(
		//		(float)rand() / (float)RAND_MAX * 10.0f - 5.0f,
		//		(float)rand() / (float)RAND_MAX * 10.0f - 5.0f,
		//		(float)rand() / (float)RAND_MAX * 10.0f - 5.0f
		//	),
		//	glm::vec3(
		//		(float)rand() / (float)RAND_MAX * 10.0f - 5.0f,
		//		(float)rand() / (float)RAND_MAX * 10.0f - 5.0f,
		//		(float)rand() / (float)RAND_MAX * 10.0f - 5.0f
		//	)/*,
		//	loadTexture("src/assets/container.jpg")*/
		//	)
		//);
		//add a cube
		addItem(new Cube(
			glm::vec3(-1.0f, 0.0f, 0.0f),
			loadTexture("src/assets/container2.png"),
			loadTexture("src/assets/container2_specular.png")
			)
		);
		addItem(new LightCube(
			glm::vec3(1.0f, 1.0f, 1.0f), //position
			glm::vec3(0.0f, 0.0f, 1.0f)
			)
		);
		
		
	}
	while (!window.closed()) {
		window.update();
		window.clear();
		window.useShader();
		draw(&window);

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();

		if (window.isKeyPressed(GLFW_KEY_W))
			m_camera.ProcessKeyboard(FORWARD, window.deltaTime);
		if (window.isKeyPressed(GLFW_KEY_S))
			m_camera.ProcessKeyboard(BACKWARD, window.deltaTime);
		if (window.isKeyPressed(GLFW_KEY_A))
			m_camera.ProcessKeyboard(LEFT, window.deltaTime);
		if (window.isKeyPressed(GLFW_KEY_D))
			m_camera.ProcessKeyboard(RIGHT, window.deltaTime);
	}
	return 0;
}