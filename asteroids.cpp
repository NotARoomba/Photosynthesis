#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include "src/includes.h"
#include "memory"

float generateRandom(float min, float max) {
	if (min > max) {
		std::swap(min, max);
	}
	return min + (float)rand() * (max - min) / (float)RAND_MAX;
}

int main(int argc, char const *argv[]) {
	Photosynthesis app(800, 600, "Photosynthesis", vec3(0, 0, 0), "src/shaders/vertex.vert", "src/shaders/fragment.frag");
	Polygon ship(vec3(0, 0, 0), {{0, 0, 0}, {8, -30, 0}, {0, -20, 0}, {-8, -30, 0}, {0, 0, 0} }, vec3(255, 255, 255), angleAxis(radians(90.0f), vec3(0, 0, 1)), true);
	Camera camera(glm::vec3(0.0f, 6.0f, 0.0f), ship.asItem());
	TextRenderer textRenderer("src/assets/Monocraft.ttf");
	app.setCamera(&camera);
    std::vector<Polygon> asteroids; 
    std::vector<Polygon> bullets; 
    int level = 4;
	srand(time(nullptr));
	while(!app.shouldClose()) {
        if (asteroids.size() == 0) {
            level++;
            for (int i = 0; i < level + 4; i++) {
                vec3 s_pos;
                do {
                   s_pos  = app.viewToWorldCoordTransform((rand() % app.getWidth()), (rand() % app.getHeight()));
				   std::cout << to_string(s_pos) << std::endl;
                } while (0.35 <= sqrt(pow(s_pos.x , 2) + pow(s_pos.y, 2)) && !ship.isTouchingItem(new Polygon({s_pos.x, s_pos.y, 0},{{0, 0, 0}, {2, -1, 0}, {3, 1, 0}, {4, 3, 0}, {2, 5, 0}, {2, 6, 0}, {3, 7, 0}, {-1, 9, 0}, {-3, 7, 0}, {-4, 8, 0}, {-6, 7, 0}, {-6, 4, 0}, {-5, 2, 0}, {-5, 0, 0}, {-3, 1, 0}, {-3, -1, 0}, {0, 0, 0}}, {255, 255, 255}, glm::quat(), true, 8)));
                Polygon asteroid({s_pos.x, s_pos.y, 0},{{0, 0, 0}, {2, -1, 0}, {3, 1, 0}, {4, 3, 0}, {2, 5, 0}, {2, 6, 0}, {3, 7, 0}, {-1, 9, 0}, {-3, 7, 0}, {-4, 8, 0}, {-6, 7, 0}, {-6, 4, 0}, {-5, 2, 0}, {-5, 0, 0}, {-3, 1, 0}, {-3, -1, 0}, {0, 0, 0}}, {255, 255, 255}, glm::quat(), true, 8);
                asteroid.addVelocity({generateRandom(-.1, .1), generateRandom(-.1, .1), 0});
                asteroids.push_back(asteroid);
            }
        }
		app.clear();
		app.update();
        for (Polygon asteroid : asteroids) {
            asteroid.move(0);
            asteroid.draw(&app);
        }
        for (Polygon bullet : bullets) {
            bullet.move(0);
            bullet.draw(&app);
        }
		ship.move(0);
		ship.draw(&app);
		textRenderer.renderText("Photosynthesis Engine, FPS: " + std::to_string(app.fps) + "  Position: " + to_string(ship.getPosition()),0.0f , app.getHeight()-20, 0.3, {255, 255, 255}, &app);
		app.swap();
		if (app.isKeyPressed(GLFW_KEY_ESCAPE))
			app.close();
		if (app.isKeyPressed(GLFW_KEY_W))
			ship.move(.1f);
			//camera.ProcessKeyboard(UP, app.deltaTime);
		// if (app.isKeyPressed(GLFW_KEY_S))
		// 	t.move(vec3(0, -2, 0));
			//camera.ProcessKeyboard(DOWN, app.deltaTime);
		if (app.isKeyPressed(GLFW_KEY_A))
			ship.move(0.0f, vec3(0, 0, 1), -2);
			//camera.ProcessKeyboard(LEFT, app.deltaTime);
		if (app.isKeyPressed(GLFW_KEY_D))
			ship.move(0.0f, vec3(0, 0, 1), 2);
			//camera.ProcessKeyboard(RIGHT, app.deltaTime);
	}
	return 0;
}
