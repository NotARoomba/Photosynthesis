#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>
#include "src/includes.h"
#include "memory"

int main(int argc, char const *argv[]) {
	Photosynthesis app(800, 600, "Photosynthesis", vec3(0, 0, 0));
	//Triangle t(vec3(-1, -1, 0), vec3(1,-1, 0), vec3(0, 1, 0), "src/assets/container.jpg" /*vec3(255, 0, 0)*/);
	//Triangle t(vec3(-1, -1, 0), vec3(1,-1, 0), vec3(0, 1, 0), vec3(255, 0, 0), true);
	Polygon t(vec3(0, 0, 0), {{0, 0, 0}, {8, -30, 0}, {0, -20, 0}, {-8, -30, 0}, {0, 0, 0} }, vec3(255, 255, 255), angleAxis(radians(90.0f), vec3(0, 0, 1)), true, 1);
	//Polygon t(vec3(0, 0, 0), {{0, 0, 0}, {8, -30, 0}, {0, -20, 0}, {-8, -30, 0}, {0, 0, 0} }, "src/assets/container.jpg", angleAxis(radians(90.0f), vec3(0, 0, 1)), 1);
	Triangle f(vec3(-1, -1, 0), vec3(1,-1, 0), vec3(0, 1, 0), vec3(255, 0, 0), true);
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 6.0f), t.asItem());
	//Camera camera = Camera(glm::vec3(0.0f, 0.0f, 6.0f), vec3(0.0f, 1.0f, 0.0f));
	app.setCamera(&camera);
	while(!app.shouldClose()) {
		app.clear();
		app.update();
		t.move(0);
		t.draw(&app);
		f.draw(&app);
		app.swap();

		if (app.isKeyPressed(GLFW_KEY_ESCAPE))
			app.close();
		if (app.isKeyPressed(GLFW_KEY_W))
			t.move(.01000f);
			//camera.ProcessKeyboard(UP, app.deltaTime);
		// if (app.isKeyPressed(GLFW_KEY_S))
		// 	t.move(vec3(0, -2, 0));
			//camera.ProcessKeyboard(DOWN, app.deltaTime);
		if (app.isKeyPressed(GLFW_KEY_A))
			t.move(0.0f, vec3(0, 0, 1), -2);
			//camera.ProcessKeyboard(LEFT, app.deltaTime);
		if (app.isKeyPressed(GLFW_KEY_D))
			t.move(0.0f, vec3(0, 0, 1), 2);
			//camera.ProcessKeyboard(RIGHT, app.deltaTime);
	}
	return 0;
}