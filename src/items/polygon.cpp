#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include "./item.h"
#include "../utils/fileUtils.h"
#include "../photosynthesis.h"
using namespace glm;


class Polygon : Item {
public:
	Polygon(std::vector<vec3> points, vec3 color, float scale) {
		this->points = points;
		this->color = color;
        this->scale = scale;
		this->model = mat4(1.0f);
        this->model = glm::scale(model, vec3(this->scale));
		init(getArray(), &this->VBO, &this->VAO);
	}
	Polygon(std::vector<vec3> points, vec3 color, bool wireframe = false, float scale = 1) {
		this->points = points;
		this->color = color;
		this->wireframe = wireframe;
        this->scale = scale;
		this->model = mat4(1.0f);
        this->model = glm::scale(model, vec3(this->scale));
		init(getArray(), &this->VBO, &this->VAO);
	}
	Polygon(std::vector<vec3> points, std::string texPath, float scale = 1) {
		this->points = points;
		this->model = mat4(1.0f);
        this->model = glm::scale(model, vec3(this->scale));
		this->texture = FileUtils::loadTexture(texPath.c_str());
		init(getArray(), &this->VBO, &this->VAO);
	}
	std::vector<vec3> getPosition() { return points; }
	void setPosition(std::vector<vec3> points) { this->points = points; }
	std::vector<float> getArray() {
        std::vector<float> data = std::vector<float>();
        for (vec3 point : this->points) {
            data.insert(data.end(), {point.x, point.y, point.z, color.x, color.y, color.z, 0.0f, 0.0f});
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
private:
	std::vector<vec3> points;

};