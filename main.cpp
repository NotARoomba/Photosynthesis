#include "src/window/window.h"
#include "src/utils/fileUtils.h"
#include "src/shaders/shader.h"
#include "src/utils/drawUtils.h"
#include "src/items/cube.h"
#include "src/items/lightCube.h"
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
		addItem(new Cube(glm::vec3(2.0f, 1.0f, 2.0f), glm::vec3(1.0f, 0.0f, 1.0f), 200.1f));
		addItem(new LightCube(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)), 1);
		//addItem(new LightCube(glm::vec3(1.0f, 1.0f, 1.0f), loadTexture("src/assets/glowstone.png")), 1);
		//add mroe lights in random positions
		for (int i = 0; i < 10; i++) {
			addItem(new LightCube(
				glm::vec3(
					(float)rand() / (float)RAND_MAX * 100.0f - 50.0f,
					(float)rand() / (float)RAND_MAX * 1.0f,
					(float)rand() / (float)RAND_MAX * 100.0f - 50.0f
				),
				glm::vec3(
					(float)rand() / (float)RAND_MAX,
					(float)rand() / (float)RAND_MAX,
					(float)rand() / (float)RAND_MAX
				)
				), 1
			);
		}
		
		
	}
	Cube *plane = new Cube(
		glm::vec3(0.0f, -0.5f, 0.0f),
		loadTexture("src/assets/floor.png")
	);
	addItem(plane);
	while (!window.closed()) {
		window.update();
		window.clear();
		window.useShader();
		//make a large flat area 
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(500.0f, 0.01f, 500.0f));
		plane->model = model;

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
		if (window.isKeyPressed(GLFW_KEY_SPACE))
			m_camera.ProcessKeyboard(UP, window.deltaTime);
		if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT))
			m_camera.ProcessKeyboard(DOWN, window.deltaTime);

	}
	return 0;
}