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
			unsigned int VAO, VBO;
			unsigned int texture;
			virtual void draw(graphics::Shader shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {std::cout << "Item::draw()" << std::endl;}
		};	
	}
}