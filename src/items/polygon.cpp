#include "./item.h"
#include "../utils/fileUtils.h"
#include "../photosynthesis.h"


class Polygon : public Item {
public:
	Polygon(glm::vec3 pos, std::vector<glm::vec3> points, glm::vec3 color, float initialAngle = 0.0f, float scale = 1) {
		this->points = points;
        this->pos = pos;
		this->color = color;
		this->initialAngle = initialAngle;
        this->scale = scale;
		this->model = glm::mat4(1.0f);
        this->model = glm::scale(model, glm::vec3(this->scale));
		init(getArray(), &this->VBO, &this->VAO);
	}
	Polygon(glm::vec3 pos, std::vector<glm::vec3> points, glm::vec3 color, bool wireframe = false, float initialAngle = 0.0f, float scale = 1) {
		this->points = points;
        this->pos = pos;
		this->color = color;
		this->wireframe = wireframe;
		this->initialAngle = initialAngle;
        this->scale = scale;
		this->model = glm::mat4(1.0f);
        this->model = glm::scale(model, glm::vec3(this->scale));
		init(getArray(), &this->VBO, &this->VAO);
	}
	Polygon(glm::vec3 pos, std::vector<glm::vec3> points, std::string texPath, float initialAngle = 0.0f, float scale = 1) {
		this->points = points;
        this->pos = pos;
		this->initialAngle = initialAngle;
		this->model = glm::mat4(1.0f);
        this->model = glm::scale(model, glm::vec3(this->scale));
		this->texture = FileUtils::loadTexture(texPath.c_str());
		init(getArray(), &this->VBO, &this->VAO);
	}
	std::vector<glm::vec3> normalizeVectorArray(std::vector<glm::vec3>& vec) {
    std::vector<glm::vec3> normalizedVec;

    float totalMagnitude = 0.0f;
    for (const glm::vec3& element : vec) {
        totalMagnitude += glm::length(element);
    }
	this->scale = totalMagnitude;
    if (totalMagnitude > 0.0f) {
        for (const glm::vec3& element : vec) {
            if (glm::length(element) > 0.0f) {
                normalizedVec.push_back(element / totalMagnitude);
            }
            else {
                normalizedVec.push_back(glm::vec3(0.0f));
            }
        }
    }
    else {
        normalizedVec = vec;
    }

    return normalizedVec;
}

	std::vector<float> getArray() {
		this->points = normalizeVectorArray(this->points);
        std::vector<float> data = std::vector<float>();
        for (glm::vec3 point : this->points) {
            data.insert(data.end(), {point.x + this->pos.x, point.y + this->pos.y, point.z + this->pos.z, color.x, color.y, color.z, point.x, point.y});
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
		if (this->texture != -1) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			app->shader->setBool("hasTexture", true);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}else {
			app->shader->setBool("hasTexture", false);
		}
		glPolygonMode(GL_FRONT_AND_BACK, this->wireframe?GL_LINE:GL_FILL);
		app->shader->enable();
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, points.size());
		glBindVertexArray(0);
		glUseProgram(0);
	}
	void move(glm::vec3 movement, glm::vec3 rotation = glm::vec3(0, 0, 1), float rotationAngle = 0.0f) {
		this->angle += rotationAngle;
		this->model = glm::mat4(1.0f);
		if (glm::length(movement) != 0) { 
			this->velocity.x += movement.x;
			this->velocity.y += movement.y;
			this->velocity.z += movement.z;
			
			this->velocity.x = this->velocity.x > this->maxVel ? this->maxVel  : this->velocity.x < -this->maxVel? -this->maxVel : this->velocity.x;
			this->velocity.y = this->velocity.y > this->maxVel ? this->maxVel  : this->velocity.y < -this->maxVel?-this->maxVel : this->velocity.y;
			this->velocity.z = this->velocity.z > this->maxVel ? this->maxVel  : this->velocity.z < -this->maxVel?-this->maxVel : this->velocity.z;
		} else if (rotationAngle == 0 && glm::length(movement) == 0) {
			this->pos += this->velocity/this->scale;
		}
		this->model = this->model * rotAroundPoint(glm::radians(this->angle-this->initialAngle), this->pos, rotation);
		this->model = glm::translate(this->model, this->pos); 

	}
	void move(float movement, glm::vec3 rotation = glm::vec3(0, 0, 1), float rotationAngle = 0.0f) {
		this->angle += rotationAngle;
		this->model = glm::mat4(1.0f);
		std::cout << to_string(this->velocity) << " " << to_string(this->pos) << " " << this->angle << std::endl;
		if (movement != 0) { 
			this->velocity.x += movement * (cosf(glm::radians(this->angle)));
			this->velocity.y += movement * (sinf(glm::radians(this->angle)));
			//this->velocity.z += movement * (tanf(glm::radians(this->angle)));

			this->velocity.x = this->velocity.x > this->maxVel ? this->maxVel  : this->velocity.x < -this->maxVel? -this->maxVel : this->velocity.x;
			this->velocity.y = this->velocity.y > this->maxVel ? this->maxVel  : this->velocity.y < -this->maxVel?-this->maxVel : this->velocity.y;
			this->velocity.z = this->velocity.z > this->maxVel ? this->maxVel  : this->velocity.z < -this->maxVel?-this->maxVel : this->velocity.z;
		} else if (rotationAngle == 0 && movement == 0) {
			this->pos += this->velocity/this->scale;
		}
		this->model = this->model * rotAroundPoint(glm::radians(this->angle-this->initialAngle), this->pos, rotation);
		this->model = glm::translate(this->model, this->pos); 
	}
private:
	std::vector<glm::vec3> points;

};