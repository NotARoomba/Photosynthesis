#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace photosynthesis {
	namespace items {
		class Item {
		public:
			glm::vec3 color;
			bool textureOn;
			bool specularOn;
			unsigned int VAO, VBO;
			unsigned int texture;
			unsigned int specular;
			virtual void draw(graphics::Window* window, glm::mat4 projection, glm::mat4 view) {};
			void init(std::vector<float> arr, unsigned int* VBO, unsigned int* VAO) {
				glGenVertexArrays(1, VAO);
				glGenBuffers(1, VBO);
				glBindBuffer(GL_ARRAY_BUFFER, *VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(arr[0]) * arr.size(),arr.data(), GL_STATIC_DRAW);
				glBindVertexArray(*VAO);

				// position attribute
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				// color coord attribute or normal
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
				glEnableVertexAttribArray(1);
				// texture coord attribute
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
				glEnableVertexAttribArray(2);
			}
		};	
	}
}