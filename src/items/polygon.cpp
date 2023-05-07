#include <glm/common.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/trigonometric.hpp>
#include <vector>
#include "./item.h"
#include "../utils/fileUtils.h"
#include "../photosynthesis.h"
using namespace glm;


class Polygon : public Item {
public:
	Polygon(vec3 pos, std::vector<vec3> points, vec3 color, float scale) {
		this->points = points;
        this->pos = pos;
		this->color = color;
        this->scale = scale;
		this->model = mat4(1.0f);
        this->model = glm::scale(model, vec3(this->scale));
		init(getArray(), &this->VBO, &this->VAO);
	}
	Polygon(vec3 pos, std::vector<vec3> points, vec3 color, bool wireframe = false, float scale = 1) {
		this->points = points;
        this->pos = pos;
		this->color = color;
		this->wireframe = wireframe;
        this->scale = scale;
		this->model = mat4(1.0f);
        this->model = glm::scale(model, vec3(this->scale));
		init(getArray(), &this->VBO, &this->VAO);
	}
	Polygon(vec3 pos, std::vector<vec3> points, std::string texPath, float scale = 1) {
		this->points = points;
        this->pos = pos;
		this->model = mat4(1.0f);
        this->model = glm::scale(model, vec3(this->scale));
		this->texture = FileUtils::loadTexture(texPath.c_str());
		init(getArray(), &this->VBO, &this->VAO);
	}
	std::vector<float> getArray() {
        std::vector<float> data = std::vector<float>();
        for (vec3 point : this->points) {
            data.insert(data.end(), {point.x + this->pos.x, point.y + this->pos.y, point.z + this->pos.z, color.x, color.y, color.z, 0.0f, 0.0f});
        }
        return data;
		// return std::vector<float>{
		// 	x.x, x.y, x.z, color.x, color.y, color.z, 0.0f, 0.0f,
		// 	y.x, y.y, y.z, color.x, color.y, color.z, 1.0f, 0.0f,
		// 	z.x, z.y, z.z, color.x, color.y, color.z, 0.5f, 1.0f
		//};
	}
	void draw(Photosynthesis* app) {
		app->shader->enable();
		glm::mat4 projection = glm::perspective(glm::radians(Photosynthesis::camera->Zoom), (float)app->getWidth() / (float)app->getHeight(), 0.1f, 100.0f);
        glm::mat4 view = Photosynthesis::camera->GetViewMatrix();
		app->shader->setVec3("color", this->color);
		app->shader->setMat4("view", view);
		app->shader->setMat4("projection", projection);
		app->shader->setMat4("model", this->model);
		if (this->texture == -1) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
		}
		glPolygonMode(GL_FRONT_AND_BACK, this->wireframe?GL_LINE:GL_FILL);
		app->shader->enable();
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_LINE_LOOP, 0, points.size());
		glBindVertexArray(0);
		glUseProgram(0);
	}
// 	void applyVelocity() {
// 	this->model = mat4(1.0f);
// 	this->model = glm::translate(this->model, vec3(0.0f));
//     this->pos += this->velocity;
// 	this->model = glm::scale(this->model, vec3(this->scale));
//     this->model = glm::rotate(this->model, radians(angle), vec3(0, 0, 1));
// 	this->model = glm::translate(this->model, this->pos);

//     // this->model = glm::translate(mat4(1.0f), this->pos) * glm::rotate(mat4(1.0f), radians(this->angle), vec3(0, 0, 1.0f));
//     // this->model = glm::scale(this->model, vec3(this->scale));
//     std::cout << to_string(this->velocity) << " " << to_string(this->pos) << " " << this->angle << std::endl;
// }

// void move(vec3 movement, vec3 rotation = vec3(0, 0, 1), float m_angle = 0.0f) {
//     this->angle += m_angle;
//     float sinAngle = sin(glm::radians(this->angle));
//     float cosAngle = cos(glm::radians(this->angle));
//     this->velocity.x += movement.x * cosAngle - movement.y * sinAngle;
//     this->velocity.y += movement.x * sinAngle + movement.y * cosAngle;
//     this->velocity.x = abs(this->velocity.x) > this->maxVel ? this->maxVel : this->velocity.x;
//     this->velocity.y = abs(this->velocity.y) > this->maxVel ? this->maxVel : this->velocity.y;
//     this->pos += this->velocity;
//     this->model = glm::translate(mat4(1.0f), this->pos) * glm::rotate(mat4(1.0f), radians(this->angle), rotation) * glm::scale(mat4(1.0f), vec3(this->scale));

// }

void move(float movement, vec3 rotation = vec3(0, 0, 1), float m_angle = 0.0f) {
    this->angle += m_angle;
	std::cout << to_string(this->velocity) << " " << to_string(this->pos) << " " << this->angle << std::endl;
	if (movement != 0) { 
    this->velocity.x += movement * (cosf(radians(this->angle)));
    this->velocity.y += movement * (sinf(radians(this->angle)));
    this->velocity.x = this->velocity.x > this->maxVel ? this->maxVel  : this->velocity.x < -this->maxVel? -this->maxVel : this->velocity.x;
    this->velocity.y = this->velocity.y > this->maxVel ? this->maxVel  : this->velocity.y < -this->maxVel?-this->maxVel : this->velocity.y;
	}
	this->model = glm::rotate(this->model, radians(m_angle), rotation);
	// this->model = glm::scale(this->model, vec3(this->scale));
	this->model = glm::translate(this->model, this->velocity);
    this->pos += this->velocity;
}
private:
	std::vector<vec3> points;

};