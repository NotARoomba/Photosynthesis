#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../items/triangle.h"
#include "../items/cube.h"
#include <iostream>
namespace photosynthesis {
    namespace graphics {
        std::vector<items::Item*> itemArr;
        void addItem(items::Item* item) {
			itemArr.push_back(item);
        }
        void draw(photosynthesis::graphics::Window* window) {
            glm::mat4 projection = glm::mat4(1.0f);
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = m_camera.GetViewMatrix();
            projection = glm::perspective(glm::radians(45.0f), (float)window->getWidth() / (float)window->getHeight(), 0.1f, 100.0f);
			for (items::Item* item : itemArr) {
				item->draw(*window->m_shader, projection, view, model);
			}
            /*for (int i = 0; i < itemArr.size(); i++) {
                itemArr[i]->draw(*window->m_shader, view, projection, model);
                std::cout << "Drawing triangle" << std::endl;
            }*/
        }
    }
}