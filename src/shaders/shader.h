#pragma once
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
using namespace glm;

class Shader {
public:
	Shader(const char* vertPath, const char* fragPath);
	void enable();
	void disable();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, mat4 value) const;
	void setVec3(const std::string& name, vec3 value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec2(const std::string& name, vec2 value) const;
private:
	int m_ShaderID;
	const char* m_vertPath;
	const char* m_fragPath;
	int load(std::string vertCode, std::string fragCode);
};