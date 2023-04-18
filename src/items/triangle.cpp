#include "./item.cpp"
#include "../photosynthesis.cpp"
using namespace glm;


class Triangle : Item {
public:
	Triangle(vec3 x, vec3 y, vec3 z, vec3 color) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->color = color;
		this->model = mat4(1.0f);
		init(getArray(), &this->VBO, &this->VAO);
	}
	vec3 getColor() { return color; }
	void setColor(vec3 color) { this->color = color; }
	std::vector<float> getArray() {
		return std::vector<float>{
			x.x, x.y, x.z, color.x, color.y, color.z, 1.0f, 0.0f,
			y.x, y.y, y.z, color.x, color.y, color.z, 0.0f, 0.0f,
			z.x, z.y, z.z, color.x, color.y, color.z, 0.0f, 1.0f
		};
	}
	void draw(Photosynthesis* app) {
		app->shader->enable();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)app->getWidth() / (float)app->getHeight(), 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
		app->shader->setVec3("color", this->color);
		app->shader->setMat4("view", view);
		app->shader->setMat4("projection", projection);
		app->shader->setMat4("model", this->model);
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);
	}
private:
	vec3 x,y,z;
};