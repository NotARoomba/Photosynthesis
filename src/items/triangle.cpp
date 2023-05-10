#include "./item.h"
#include "../photosynthesis.h"
#include "../utils/fileUtils.h"
#include <cstddef>
#include <glm/gtx/string_cast.hpp>
#include <vector>


class Triangle : public Item {
public:
	Triangle(glm::vec3 x, glm::vec3 y, glm::vec3 z, glm::vec3 color) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->color = color;
		this->model = glm::mat4(1.0f);
		init(getArray(), &this->VBO, &this->VAO);
	}
	Triangle(glm::vec3 x, glm::vec3 y, glm::vec3 z, glm::vec3 color, bool wireframe) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->color = color;
		this->wireframe = wireframe;
		this->model = glm::mat4(1.0f);
		init(getArray(), &this->VBO, &this->VAO);
	}
	Triangle(glm::vec3 x, glm::vec3 y, glm::vec3 z, std::string texPath) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->model = glm::mat4(1.0f);
		this->texture = FileUtils::loadTexture(texPath.c_str());
		init(getArray(), &this->VBO, &this->VAO);
	}
	std::vector<float> getArray() {
		return std::vector<float>{
			x.x, x.y, x.z, color.x, color.y, color.z, 0.0f, 0.0f,
			y.x, y.y, y.z, color.x, color.y, color.z, 1.0f, 0.0f,
			z.x, z.y, z.z, color.x, color.y, color.z, 0.5f, 1.0f
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
		if (this->texture != -1) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			app->shader->setBool("hasTexture", true);
		} else {
			app->shader->setBool("hasTexture", false);
		}
		glPolygonMode(GL_FRONT_AND_BACK, this->wireframe?GL_LINE:GL_FILL);
		app->shader->enable();
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);
	}

void move(float movement, glm::vec3 rotation = glm::vec3(0, 0, 1), float rotationAngle = 0.0f) {
    this->angle += rotationAngle;
	this->model = glm::mat4(1.0f);
	if (movement != 0) { 
		this->velocity.x += movement * (cosf(glm::radians(this->angle)));
		this->velocity.y += movement * (sinf(glm::radians(this->angle)));
		this->velocity.x = this->velocity.x > this->maxVel ? this->maxVel  : this->velocity.x < -this->maxVel? -this->maxVel : this->velocity.x;
		this->velocity.y = this->velocity.y > this->maxVel ? this->maxVel  : this->velocity.y < -this->maxVel?-this->maxVel : this->velocity.y;
	} else if (rotationAngle == 0 && movement == 0) {
		this->pos += this->velocity/this->scale;
	}
	this->model = this->model * rotAroundPoint(glm::radians(this->angle-this->initialAngle), this->pos, rotation);
	this->model = glm::translate(this->model, this->pos); 
}
private:
	glm::vec3 x,y,z;
};