#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../items/triangle.h"
#include "../items/cube.h"
#include "../items/lightCube.h"
#include <iostream>
namespace photosynthesis {
    namespace graphics {
        std::vector<items::Item*> itemArr;
        void addItem(items::Item* item) {
			itemArr.push_back(item);
        }
        void draw(photosynthesis::graphics::Window* window) {
            glm::mat4 projection = glm::perspective(glm::radians(m_camera.Zoom), (float)window->getWidth() / (float)window->getHeight(), 0.1f, 100.0f);
            glm::mat4 view = m_camera.GetViewMatrix();
			for (items::Item* item : itemArr) {
				item->draw(window, projection, view);
			}
        }
    }
}