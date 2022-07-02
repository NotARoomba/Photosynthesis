#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace photosynthesis {
	namespace graphics {
        unsigned int VBO, VAO;
        std::vector<float> vertices;
        void update() {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // color coord attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            /*glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(VAO);*/
        }
        void addTriangle(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3, glm::vec3 color) {
            vertices.insert(vertices.end(), {
                 pos1.x, pos1.y, pos1.z, color.r, color.g, color.b,
                 pos2.x, pos2.y, pos2.z, color.r, color.g, color.b,
                 pos3.x, pos3.y, pos3.z, color.r, color.g, color.b });
            update();
        }
        void draw(photosynthesis::graphics::Window* window) {
            glm::mat4 projection = glm::mat4(1.0f);
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = m_camera.GetViewMatrix();
            projection = glm::perspective(glm::radians(45.0f), (float)window->getWidth() / (float)window->getHeight(), 0.1f, 100.0f);
            window->m_shader->setMat4("view", view);
            window->m_shader->setMat4("projection", projection);
			window->m_shader->setMat4("model", model);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, vertices.size()/6);
        }
	}
}