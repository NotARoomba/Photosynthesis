#pragma once
#include <glm/common.hpp>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/trigonometric.hpp>
#include <vector>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include <type_traits>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Item {
public:
	glm::vec3 color;
	glm::mat4 model;
	glm::quat initialRotation, rotation;
	bool wireframe = false;
	unsigned int texture = -1;
	float scale, magnitude = 1;
	glm::vec3 pos;
	glm::vec3 velocity = glm::vec3(0.0f);
	float maxVel = 3.0f;
	unsigned int VAO, VBO;
	glm::vec3 getPosition() {return this->pos;};
	void setPosition(glm::vec3 pos);
	void setPosition(glm::vec3 x, glm::vec3 y, glm::vec3 z);
	glm::mat4 getModel();
	void setModel(glm::mat4 model);
	void draw();
	std::vector<glm::vec3> getBoundingBox() {
		glm::vec3 min = this->points[0];
		glm::vec3 max = this->points[0];
		for (glm::vec3 point : this->points) { 
			min.x = glm::min(point.x, min.x);
			min.y = glm::min(point.y, min.y);
			min.z = glm::min(point.z, min.z);

			max.x = glm::min(point.x, max.x);
			max.y = glm::min(point.y, max.y);
			max.z = glm::min(point.z, max.z);
		}
		return {min, max};
	}
	Item* asItem();
	inline void init(std::vector<float> arr, unsigned int* VBO, unsigned int* VAO) {
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
	std::vector<glm::vec3> normalizeVectorArray(std::vector<glm::vec3>& vec) {
		std::vector<glm::vec3> normalizedVec;

		float totalMagnitude = 0.0f;
		for (const glm::vec3& element : vec) {
			totalMagnitude += glm::length(element);
		}
		this->magnitude = totalMagnitude;
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
	}
	glm::mat4 rotAroundPoint(const glm::vec3& point, const glm::quat& rotation) {
		glm::mat4 t1 = glm::translate(glm::mat4(1),-point);
		glm::mat4 t2 = glm::translate(glm::mat4(1),point);
		return t2 * glm::mat4_cast(rotation) * t1;
	}
	void addVelocity(glm::vec3 vel) {
		this->velocity += vel;
	}
	void move(glm::vec3 movement);
	void move(float movement);
	
	bool isTouchingItem(Item* item) {
		glm::vec3 min = item->getBoundingBox()[0];
		glm::vec3 max = item->getBoundingBox()[1];
		bool isInside = false;
		for (glm::vec3 p : this->points) {
		if (p.x < min.x || p.x > max.x || p.y < min.y || p.y > max.y /*|| p.z < min.z || p.z > max.z */) {
			return false;
		}

		//int i = 0, j = item->getArray().size() - 1;
		for (int i = 0, j = (item->getArray().size()/3)- 1; i < item->getArray().size(); j = i++) {
			if ( (item->getArray()[i+1] > p.y) != (item->getArray()[j+1] > p.y) &&
					p.x < (item->getArray()[j] - item->getArray()[i]) * (p.y - item->getArray()[i+1]) / (item->getArray()[j+1] - item->getArray()[i+1]) + item->getArray() [i] ) {
				isInside = !isInside;
			}
		}
		if (isInside) return isInside;
		}
		return isInside;
	}
private: 
	std::vector<glm::vec3> points;
};