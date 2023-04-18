#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "src/items/triangle.cpp"

int main(int argc, char const *argv[]) {
	Photosynthesis app(800, 600);
	Triangle t(vec3(0.5, 0.5, 0), vec3(0.5,-0.5, 0), vec3(-0.5, 0.5, 0), vec3(255, 0, 0));
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