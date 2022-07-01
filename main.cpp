#include "src/window/window.h"
#include "src/utils/fileUtils.h"
#include "src/shaders/shader.h"
#include "src/utils/drawUtils.h"
#include <iostream>

using namespace photosynthesis;
using namespace graphics;

int main() {
	Window window("Photosynthesis Engine", 960, 540);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	while (!window.closed()) {
		window.clear();
		window.useShader();
		drawTriangle(glm::vec3( 0.0f,  0.0f, 0.0f), glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		
		window.update();
	}
	return 0;
}