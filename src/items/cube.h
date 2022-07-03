#pragma once
#include "item.h"
#include "../shaders/shader.h"
namespace photosynthesis {
	namespace items {
		class Cube : public Item {
		public:
			Cube(glm::vec3 position, glm::vec3 color) {
				this->position = position;
				this->color = color;
				this->textureOn = false;
				glGenVertexArrays(1, &VAO);
				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(getArray()[0]) * getArray().size(), getArray().data(), GL_STATIC_DRAW);
				glBindVertexArray(VAO);

				// position attribute
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				// color coord attribute
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
				glEnableVertexAttribArray(1);
				// texture coord attribute
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
				glEnableVertexAttribArray(2);

				/*glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(VAO);*/
			}
			Cube(glm::vec3 position, glm::vec3 color, unsigned int texture) {
				this->position = position;
				this->color = color;
				this->texture = texture;
				this->textureOn = true;
				glGenVertexArrays(1, &VAO);
				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(getArray()[0]) * getArray().size(), getArray().data(), GL_STATIC_DRAW);
				glBindVertexArray(VAO);

				// position attribute
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				// color coord attribute
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
				glEnableVertexAttribArray(1);
				// texture coord attribute
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
				glEnableVertexAttribArray(2);

				/*glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(VAO);*/
			}
			std::vector<float> getArray() {
				return std::vector<float>{
			-0.5f, -0.5f, -0.5f,  color.r, color.g, color.b, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  color.r, color.g, color.b, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  color.r, color.g, color.b, 1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  color.r, color.g, color.b, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  color.r, color.g, color.b, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  color.r, color.g, color.b, 0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  color.r, color.g, color.b, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  color.r, color.g, color.b, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  color.r, color.g, color.b, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  color.r, color.g, color.b, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  color.r, color.g, color.b, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  color.r, color.g, color.b, 0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  color.r, color.g, color.b, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  color.r, color.g, color.b, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  color.r, color.g, color.b, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  color.r, color.g, color.b, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  color.r, color.g, color.b, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  color.r, color.g, color.b, 1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  color.r, color.g, color.b, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  color.r, color.g, color.b, 1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  color.r, color.g, color.b, 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  color.r, color.g, color.b, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  color.r, color.g, color.b, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  color.r, color.g, color.b, 1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  color.r, color.g, color.b, 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  color.r, color.g, color.b, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  color.r, color.g, color.b, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  color.r, color.g, color.b, 1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  color.r, color.g, color.b, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  color.r, color.g, color.b, 0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  color.r, color.g, color.b, 0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  color.r, color.g, color.b, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  color.r, color.g, color.b, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  color.r, color.g, color.b, 1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  color.r, color.g, color.b, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  color.r, color.g, color.b, 0.0f, 1.0f
				};
			}
			void draw(graphics::Shader shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model) override {
				shader.enable();
				shader.setVec3("color", color);
				shader.setMat4("view", view);
				shader.setMat4("projection", projection);
				shader.setMat4("model", model);
				shader.setBool("textureOn", textureOn);
				if (textureOn) {
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, texture);
				}
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);
				glUseProgram(0);
			}
		private:
			glm::vec3 position;
		};
	}
}
