#include "src/window/window.h"
#include "src/maths/vec2.h"
#include <GLFW/glfw3.h>

using namespace photosynthesis;
using namespace graphics;
using namespace maths;


int main() {
	Window window("Photosynthesis Engine", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
	double x, y;
	while (!window.closed()) {
		window.getMousePosition(x, y);
		std::cout << x << " " << y << std::endl;
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