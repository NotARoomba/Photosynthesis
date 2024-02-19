#include "./item.h"
#include "../photosynthesis.h"
#include "../utils/fileUtils.h"
#include <cstddef>
#include <glm/gtx/string_cast.hpp>
#include <vector>


class Grid : public Item {
public:
	Grid(glm::vec3 size, glm::vec3 color) {
		this->size = size;
		this->color = color;
		this->model = glm::mat4(1.0f);
		init(getArray(), &this->VBO, &this->VAO);
	}
	Grid(glm::vec3 size, glm::vec3 color, bool wireframe) {
		this->size = size;
		this->color = color;
		this->wireframe = wireframe;
		this->model = glm::mat4(1.0f);
		init(getArray(), &this->VBO, &this->VAO);
	}
	std::vector<float> getArray() {
        // std::vector<float> data = std::vector<float>();
        // for (float i = 0; i < this->size.x; i++) {
        //  for (float j = 0; j < this->size.y; j++) {
        //     for (float k = 0; k < this->size.z; k++) {
        //     data.insert(data.end(), {i, j, k, color.x, color.y, color.z, 0.0f, 0.0f});
        //     }
        //  }
        // }
        // return data;
		return std::vector<float>{
			 // first triangle
     0.5f,  0.5f, 0.0f, color.x, color.y, color.z, 0.0f, 0.0f, // top right
     0.5f, -0.5f, 0.0f,  color.x, color.y, color.z, 0.0f, 0.0f, // bottom right
    -0.5f,  0.5f, 0.0f,  color.x, color.y, color.z, 0.0f, 0.0f, // top left 
    // second triangle
     0.5f, -0.5f, 0.0f,  color.x, color.y, color.z, 0.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  color.x, color.y, color.z, 0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   color.x, color.y, color.z, 0.0f, 0.0f // top left
		};
	}
	void draw(Photosynthesis* app) {
		app->shader->enable();
		glm::mat4 projection = glm::perspective(glm::radians(Photosynthesis::camera->Zoom), (float)app->getWidth() / (float)app->getHeight(), 0.1f, 100.0f);
        glm::mat4 view = Photosynthesis::camera->GetViewMatrix();
		app->shader->setMat4("model", this->model);
		app->shader->setMat4("view", view);
		app->shader->setMat4("projection", projection);
		app->shader->setVec3("color", this->color);
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, this->wireframe?GL_LINE:GL_FILL);
		app->shader->enable();
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	void move(glm::vec3 movement, glm::vec3 rotationAxis = glm::vec3(0, 0, 1), float rotationAngle = 0.0f) {
		this->rotation = glm::normalize(this->rotation * glm::angleAxis(glm::radians(rotationAngle), rotationAxis));
		this->model = glm::mat4(1.0f);
		if (glm::length(movement) != 0) { 
			this->velocity.x += movement.x;
			this->velocity.y += movement.y;
			this->velocity.z += movement.z;
			
			this->velocity.x = this->velocity.x > this->maxVel ? this->maxVel  : this->velocity.x < -this->maxVel? -this->maxVel : this->velocity.x;
			this->velocity.y = this->velocity.y > this->maxVel ? this->maxVel  : this->velocity.y < -this->maxVel?-this->maxVel : this->velocity.y;
			this->velocity.z = this->velocity.z > this->maxVel ? this->maxVel  : this->velocity.z < -this->maxVel?-this->maxVel : this->velocity.z;
		} else if (rotationAngle == 0 && glm::length(movement) == 0) {
			this->pos += this->velocity/this->magnitude;
		}
		this->model = this->model * glm::scale(glm::mat4(1.0f), glm::vec3(this->scale)) * rotAroundPoint(this->pos/this->scale, this->rotation);
		this->model = glm::translate(this->model, this->pos/this->scale); 

	}
	void move(float movement, glm::vec3 rotationAxis = glm::vec3(0, 0, 1), float rotationAngle = 0.0f) {
		this->rotation = glm::normalize(this->rotation * glm::angleAxis(glm::radians(rotationAngle), rotationAxis));
		this->model = glm::mat4(1.0f);
		//std::cout << to_string(this->velocity) << " " << to_string(this->pos) << " " << to_string(degrees(glm::eulerAngles(this->initialRotation))) << std::endl;
		if (movement != 0) { 
			this->velocity.x += movement * (cosf(glm::eulerAngles(this->rotation).z + glm::eulerAngles(this->initialRotation).z));
			this->velocity.y += movement * (sinf(glm::eulerAngles(this->rotation).z + glm::eulerAngles(this->initialRotation).z));

			this->velocity.x = this->velocity.x > this->maxVel ? this->maxVel  : this->velocity.x < -this->maxVel? -this->maxVel : this->velocity.x;
			this->velocity.y = this->velocity.y > this->maxVel ? this->maxVel  : this->velocity.y < -this->maxVel?-this->maxVel : this->velocity.y;
			this->velocity.z = this->velocity.z > this->maxVel ? this->maxVel  : this->velocity.z < -this->maxVel?-this->maxVel : this->velocity.z;
		} else if (rotationAngle == 0 && movement == 0) {
			this->pos += this->velocity/this->magnitude;
		}
		this->model = this->model * glm::scale(glm::mat4(1.0f), glm::vec3(this->scale)) * rotAroundPoint(this->pos/this->scale, this->rotation);
		this->model = glm::translate(this->model, this->pos/this->scale); 
	}
private:
	glm::vec3 size;
};