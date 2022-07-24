#pragma once
#include "item.h"
#include "../shaders/shader.h"
namespace photosynthesis {
	namespace items {
		class Cube : public Item {
		public:
			Cube(glm::vec3 position, glm::vec3 color, float shininess) {
				this->position = position;
				this->color = color;
				this->shininess = shininess;
				this->textureOn = false;
				this->specularOn = false;
				this->model = glm::mat4(1.0f);
				init(getArray(), &this->VBO, &this->VAO);
			}
			Cube(glm::vec3 position, unsigned int texture) {
				this->position = position;
				this->texture = texture;
				this->textureOn = true;
				this->specularOn = false;
				this->model = glm::mat4(1.0f);
				init(getArray(), &this->VBO, &this->VAO);
			}
			Cube(glm::vec3 position, unsigned int texture, unsigned int specular) {
				this->position = position;
				this->texture = texture;
				this->textureOn = true;
				this->specular = specular;
				this->specularOn = true;
				this->model = glm::mat4(1.0f);
				init(getArray(), &this->VBO, &this->VAO);
			}
			std::vector<float> getArray() {
				return std::vector<float>{
					// positions          // normals           // texture coords
					-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
					 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
					 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
					 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
					-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
					-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

					-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
					 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
					 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
					 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
					-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
					-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

					-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
					-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
					-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
					-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
					-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
					-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

					 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
					 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
					 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
					 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
					 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
					 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

					-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
					 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
					 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
					 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
					-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
					-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

					-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
					 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
					 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
					 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
					-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
					-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
				};
			}
			glm::vec3 getPosition() {
				return position;
			}
			void draw(graphics::Window* window, glm::mat4 projection, glm::mat4 view, std::vector<Item*> *lights) override {
				window->m_shader->enable();
				this->model = glm::translate(this->model, position);
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
					glBindTexture(GL_TEXTURE_2D, this->texture);
				}
				else {
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, 0);
					window->m_shader->setFloat("material.shininess", shininess);
				}
				if (this->specularOn) {
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, this->specular);
				} else {
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, 0);
				}
				window->m_shader->enable();
				glBindVertexArray(this->VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);
				glUseProgram(0);
			}
		private:
			glm::vec3 position;
		};
	}
}
