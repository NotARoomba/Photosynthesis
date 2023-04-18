#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "src/items/triangle.cpp"

int main(int argc, char const *argv[]) {
	Photosynthesis app(800, 600);
	Triangle t(vec3(12, 0, 0), vec3(6, 6, 0), vec3(18, 6, 0), vec3(255, 255, 255));
	while(!app.shouldClose()) {
		app.clear();
		app.update();
		t.draw(&app);
	}
	return 0;
}