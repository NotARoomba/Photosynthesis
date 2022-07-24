#pragma once
#include "item.h"
#include "../shaders/shader.h"

namespace photosynthesis {
	namespace items {
		class Triangle : public Item
		{
		public:
			Triangle(glm::vec3 x, glm::vec3 y, glm::vec3 z, glm::vec3 color, float shininess) {
				this->x = x;
				this->y = y;
				this->z = z;
				this->color = color;
				this->shininess = shininess;
				this->textureOn = false;
				this->model = glm::mat4(1.0f);
				init(getArray(), &this->VBO, &this->VAO);
			}
			Triangle(glm::vec3 x, glm::vec3 y, glm::vec3 z, unsigned int texture) {
				this->x = x;
				this->y = y;
				this->z = z;
				this->texture = texture;
				this->textureOn = true;
				this->model = glm::mat4(1.0f);
				init(getArray(), &this->VBO, &this->VAO);
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
			void draw(graphics::Window* window, glm::mat4 projection, glm::mat4 view, std::vector<Item*> *lights) override {
				window->m_shader->enable();
				window->m_shader->setVec3("color", this->color);
				window->m_shader->setMat4("view", view);
				window->m_shader->setMat4("projection", projection);
				window->m_shader->setMat4("model", this->model);
				window->m_shader->setBool("textureOn", this->textureOn);
				this->model = glm::mat4(1.0f);
				this->lights(window, lights);
				window->lighting();
				if (this->textureOn) {
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, texture);
				}
				else {
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, 0);
					window->m_shader->setFloat("material.shininess", shininess);
				}
				window->m_shader->enable();
				glBindVertexArray(this->VAO);
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