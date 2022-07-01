#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace photosynthesis {
	void drawTriangle(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3, glm::vec3 color) {
		unsigned int VBO, VAO;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        float vertices[] = {
            pos1.x, pos1.y, pos1.z, color.r, color.g, color.b,
            pos2.x, pos2.y, pos2.z, color.r, color.g, color.b,
            pos3.x, pos3.y, pos3.z, color.r, color.g, color.b
        };

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color coord attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}