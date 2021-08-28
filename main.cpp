#include "src/window/window.h"
#include <GLFW/glfw3.h>
using namespace photosynthesis;
using namespace graphics;

int main() {
	Window window("Photosynthesis Engine", 800, 600);
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	while (!window.closed()) {
		window.clear();
		window.update();
	}
	return 0;
}