#pragma once

#include "cube.h"

namespace photosynthesis {
	namespace items {
		class LightCube : public Cube {
		public:
			LightCube(glm::vec3 position, glm::vec3 color) : Cube(position, color, shininess) {
				this->position = position;
				this->color = color;
				this->textureOn = false;
				this->model = glm::mat4(1.0f);
				init(getArray(), &this->VBO, &this->VAO);
			}
			LightCube(glm::vec3 position, unsigned int texture) : Cube(position, texture) {
				this->position = position;
				this->texture = texture;
				this->textureOn = true;
				this->model = glm::mat4(1.0f);
				init(getArray(), &this->VBO, &this->VAO);
			}
			glm::vec3 getPosition() {
				return position;
			}
			std::vector<float> getArray() {
				return !this->textureOn ? std::vector<float>{
					-0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f, 0.0f,
						0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 1.0f, 0.0f,
						0.5f, 0.5f, -0.5f, color.r, color.g, color.b, 1.0f, 1.0f,
						0.5f, 0.5f, -0.5f, color.r, color.g, color.b, 1.0f, 1.0f,
						-0.5f, 0.5f, -0.5f, color.r, color.g, color.b, 0.0f, 1.0f,
						-0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f, 0.0f,

						-0.5f, -0.5f, 0.5f, color.r, color.g, color.b, 0.0f, 0.0f,
						0.5f, -0.5f, 0.5f, color.r, color.g, color.b, 1.0f, 0.0f,
						0.5f, 0.5f, 0.5f, color.r, color.g, color.b, 1.0f, 1.0f,
						0.5f, 0.5f, 0.5f, color.r, color.g, color.b, 1.0f, 1.0f,
						-0.5f, 0.5f, 0.5f, color.r, color.g, color.b, 0.0f, 1.0f,
						-0.5f, -0.5f, 0.5f, color.r, color.g, color.b, 0.0f, 0.0f,

						-0.5f, 0.5f, 0.5f, color.r, color.g, color.b, 1.0f, 0.0f,
						-0.5f, 0.5f, -0.5f, color.r, color.g, color.b, 1.0f, 1.0f,
						-0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f, 1.0f,
						-0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f, 1.0f,
						-0.5f, -0.5f, 0.5f, color.r, color.g, color.b, 0.0f, 0.0f,
						-0.5f, 0.5f, 0.5f, color.r, color.g, color.b, 1.0f, 0.0f,

						0.5f, 0.5f, 0.5f, color.r, color.g, color.b, 1.0f, 0.0f,
						0.5f, 0.5f, -0.5f, color.r, color.g, color.b, 1.0f, 1.0f,
						0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f, 1.0f,
						0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f, 1.0f,
						0.5f, -0.5f, 0.5f, color.r, color.g, color.b, 0.0f, 0.0f,
						0.5f, 0.5f, 0.5f, color.r, color.g, color.b, 1.0f, 0.0f,

						-0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f, 1.0f,
						0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 1.0f, 1.0f,
						0.5f, -0.5f, 0.5f, color.r, color.g, color.b, 1.0f, 0.0f,
						0.5f, -0.5f, 0.5f, color.r, color.g, color.b, 1.0f, 0.0f,
						-0.5f, -0.5f, 0.5f, color.r, color.g, color.b, 0.0f, 0.0f,
						-0.5f, -0.5f, -0.5f, color.r, color.g, color.b, 0.0f, 1.0f,

						-0.5f, 0.5f, -0.5f, color.r, color.g, color.b, 0.0f, 1.0f,
						0.5f, 0.5f, -0.5f, color.r, color.g, color.b, 1.0f, 1.0f,
						0.5f, 0.5f, 0.5f, color.r, color.g, color.b, 1.0f, 0.0f,
						0.5f, 0.5f, 0.5f, color.r, color.g, color.b, 1.0f, 0.0f,
						-0.5f, 0.5f, 0.5f, color.r, color.g, color.b, 0.0f, 0.0f,
						-0.5f, 0.5f, -0.5f, color.r, color.g, color.b, 0.0f, 1.0f
				} :
				std::vector<float>{
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
			void draw(graphics::Window* window, glm::mat4 projection, glm::mat4 view, std::vector<Item*>* lights) override {
				window->m_lightShader->enable();
				//this->model = glm::scale(this->model, glm::vec3(0.5f, 0.5f, 0.5f));
				this->model = glm::translate(this->model, position);
				window->m_lightShader->setVec3("color", this->color);
				window->m_lightShader->setMat4("view", view);
				window->m_lightShader->setMat4("projection", projection);
				window->m_lightShader->setMat4("model", this->model);
				window->m_lightShader->setBool("textureOn", this->textureOn);
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
				}
				window->m_lightShader->enable();
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