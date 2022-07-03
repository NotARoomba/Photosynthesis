#pragma once
#include "item.h"
#include "../shaders/shader.h"

namespace photosynthesis {
	namespace items {
		class Triangle : public Item
		{
		public:
			Triangle(glm::vec3 x, glm::vec3 y, glm::vec3 z, glm::vec3 color) {
				this->x = x;
				this->y = y;
				this->z = z;
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
				/*glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
				glEnableVertexAttribArray(2);*/

				/*glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(VAO);*/
			}
			Triangle(glm::vec3 x, glm::vec3 y, glm::vec3 z, glm::vec3 color, unsigned int texture) {
				this->x = x;
				this->y = y;
				this->z = z;
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
			glm::vec3 getColor() { return color; }
			void setColor(glm::vec3 color) { this->color = color; }
			std::vector<float> getArray() {
				return std::vector<float>{
					x.x, x.y, x.z, color.x, color.y, color.z, 1.0f, 0.0f,
					y.x, y.y, y.z, color.x, color.y, color.z, 0.0f, 0.0f,
					z.x, z.y, z.z, color.x, color.y, color.z, 0.0f, 1.0f
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
					shader.setInt("texture", 0);
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, texture);
				}
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glBindVertexArray(0);
				glUseProgram(0);
			}
		private:
			glm::vec3 x;
			glm::vec3 y;
			glm::vec3 z;
		};
	}
}