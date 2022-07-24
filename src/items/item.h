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
			float shininess;
			glm::mat4 model;
			bool textureOn;
			bool specularOn;
			unsigned int VAO, VBO;
			unsigned int texture;
			unsigned int specular;
			virtual void draw(graphics::Window* window, glm::mat4 projection, glm::mat4 view, std::vector<Item*> *lights) {};
			virtual glm::vec3 getPosition() {return glm::vec3(0, 0, 0);};
			virtual void setPosition(glm::vec3 pos) {};
			virtual glm::mat4 getModel() {return model;};
			virtual void setModel(glm::mat4 model) {this->model = model;};
			void lights(graphics::Window* window, std::vector<Item*>* lights) {
				for (int i = 0; i < lights->size(); i++) {
					
					std::string n = std::to_string(i);
					window->m_shader->setVec3("pointLights[" + n + "].position", lights->at(i)->getPosition());
					if (lights->at(i)->textureOn) {
						//TODO get color from texture
						//window->m_shader->setVec3("pointLights[" + n + "].ambient", lights->at(i)->color.x * 0.1f, lights->at(i)->color.y * 0.1f, lights->at(i)->color.z * 0.1f);
						//window->m_shader->setVec3("pointLights[" + n + "].diffuse", lights->at(i)->color);
						//window->m_shader->setVec3("pointLights[" + n + "].specular", lights->at(i)->color);
					}
					else {
						window->m_shader->setVec3("pointLights[" + n + "].ambient", lights->at(i)->color.x * 0.1f, lights->at(i)->color.y * 0.1f, lights->at(i)->color.z * 0.1f);
						window->m_shader->setVec3("pointLights[" + n + "].diffuse", lights->at(i)->color);
						window->m_shader->setVec3("pointLights[" + n + "].specular", lights->at(i)->color);
					}
					window->m_shader->setFloat("pointLights[" + n + "].constant", 1.0f);
					window->m_shader->setFloat("pointLights[" + n + "].linear", 0.09);
					window->m_shader->setFloat("pointLights[" + n + "].quadratic", 0.032);
				}
			}
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