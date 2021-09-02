#include "src/window/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileUtils.h"
#include "src/shaders/shader.h"
#include <GLFW/glfw3.h>
#include <iostream>

using namespace photosynthesis;
using namespace graphics;
using namespace maths;

int main() {
	Window window("Photosynthesis Engine", 960, 540);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

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