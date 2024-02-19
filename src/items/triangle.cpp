#include "./item.h"
#include "../photosynthesis.h"
#include "../utils/fileUtils.h"
#include <cstddef>
#include <glm/gtx/string_cast.hpp>
#include <vector>


class Triangle : public Item {
public:
	Triangle(std::vector<glm::vec3> points, glm::vec3 color) {
		this->points = points;
		this->color = color;
		this->model = glm::mat4(1.0f);
		init(getArray(), &this->VBO, &this->VAO);
	}
	Triangle(std::vector<glm::vec3> points, glm::vec3 color, bool wireframe) {
		this->points = points;
		this->color = color;
		this->wireframe = wireframe;
		this->model = glm::mat4(1.0f);
		init(getArray(), &this->VBO, &this->VAO);
	}
	Triangle(std::vector<glm::vec3> points, std::string texPath) {
		this->points = points;
		this->model = glm::mat4(1.0f);
		this->texture = FileUtils::loadTexture(texPath.c_str());
		init(getArray(), &this->VBO, &this->VAO);
	}
	std::vector<float> getArray() {
	// 	this->points = normalizeVectorArray(this->points);
    //     std::vector<float> data = std::vector<float>();
    //     for (glm::vec3 point : this->points) {
    //         data.insert(data.end(), {point.x + this->pos.x, point.y + this->pos.y, point.z + this->pos.z, color.x, color.y, color.z, point.x, point.y});
    //     }
    //  return data;
		return std::vector<float>{
			points[0].x, points[0].y, points[0].z, color.x, color.y, color.z, 0.0f, 0.0f,
			points[1].x, points[1].y, points[1].z, color.x, color.y, color.z, 1.0f, 0.0f,
			points[2].x, points[2].y, points[2].z, color.x, color.y, color.z, 0.5f, 1.0f
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
		glDisable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, this->wireframe?GL_LINE:GL_FILL);
		app->shader->enable();
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
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
	std::vector<glm::vec3> points;
};