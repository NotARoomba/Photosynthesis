#include <iostream>
#include "src/includes.h"

int main(int argc, char const *argv[]) {
	Photosynthesis app(800, 600, "Photosynthesis", vec3(0, 0, 0));
	//Triangle t(vec3(-1, -1, 0), vec3(1,-1, 0), vec3(0, 1, 0), "src/assets/container.jpg" /*vec3(255, 0, 0)*/);
	//Triangle t(vec3(-1, -1, 0), vec3(1,-1, 0), vec3(0, 1, 0), vec3(255, 0, 0), true);
	Polygon t({{0, 0, 0}, {8, -30, 0}, {0, -20, 0}, {-8, -30, 0}, {0, 0, 0} }, vec3(255, 255, 255), false, 0.01);
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 6.0f));
	app.setCamera(&camera);
	while(!app.shouldClose()) {
		app.clear();
		app.update();
		t.draw(&app);
		app.swap();

		if (app.isKeyPressed(GLFW_KEY_ESCAPE))
			app.close();
		if (app.isKeyPressed(GLFW_KEY_W))
			camera.ProcessKeyboard(UP, app.deltaTime);
		if (app.isKeyPressed(GLFW_KEY_S))
			camera.ProcessKeyboard(DOWN, app.deltaTime);
		if (app.isKeyPressed(GLFW_KEY_A))
			camera.ProcessKeyboard(LEFT, app.deltaTime);
		if (app.isKeyPressed(GLFW_KEY_D))
			camera.ProcessKeyboard(RIGHT, app.deltaTime);
	}
	return 0;
}