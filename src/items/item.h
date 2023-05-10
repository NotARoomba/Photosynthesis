#pragma once
#include <glm/common.hpp>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/fwd.hpp>
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
	float angle = 0.0f;
	float initialAngle = 0.0f;
	bool wireframe = false;
	unsigned int texture = -1;
	float scale = 1;
	glm::vec3 pos;
	glm::vec3 velocity = glm::vec3(0.0f);
	float maxVel = 3.0f;
	unsigned int VAO, VBO;
	glm::vec3 getPosition() {return this->pos;};
	void setPosition(glm::vec3 pos);
	void setPosition(glm::vec3 x, glm::vec3 y, glm::vec3 z);
	glm::mat4 getModel();
	void setModel(glm::mat4 model);
	void setAngle(float angle) { this->angle = angle;};
	float getAngle() {return this->angle;};
	void draw();
	Item* asItem();
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
	glm::mat4 rotAroundPoint(float rad, const glm::vec3& point, const glm::vec3& axis) {
		glm::mat4 t1 = glm::translate(glm::mat4(1),-point);
		glm::mat4 r = glm::rotate(glm::mat4(1),rad,axis);
		glm::mat4 t2 = glm::translate(glm::mat4(1),point);
		return t2 * r * t1;
	}
	void move(glm::vec3 movement);
	void move(float movement);
private: 
	std::vector<glm::vec3> points;
};