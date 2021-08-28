#include "src/window/window.h"
#include <GLFW/glfw3.h>
using namespace photosynthesis;
using namespace graphics;

int main() {
	Window window("Photosynthesis Engine", 800, 600);
	while (!window.closed()) {
		window.update();
	}
	return 0;
}