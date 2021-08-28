#include "src/window/window.h"
#include <GLFW/glfw3.h>
using namespace photosynthesis;
using namespace graphics;

int main() {
	Window window("Photosynthesis Engine", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
	while (!window.closed()) {
		window.clear();
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		window.update();
	}
	return 0;
}