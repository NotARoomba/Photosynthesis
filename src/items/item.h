#pragma once
#include <iostream>
#include <type_traits>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

class Item {
public:
	vec3 color;
	mat4 model;
	bool wireframe = false;
	unsigned int texture = -1;
	float scale = 1;
	unsigned int VAO, VBO;
	std::vector<vec3> getPosition();
	void setPosition(glm::vec3 pos);
	void setPosition(glm::vec3 x, glm::vec3 y, glm::vec3 z);
	glm::mat4 getModel();
	void setModel(glm::mat4 model);
	void draw();
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
private: 
	vec3 x, y, z;
	std::vector<vec3> points;
};