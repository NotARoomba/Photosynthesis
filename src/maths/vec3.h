#pragma once
#include <iostream>

namespace photosynthesis {
	namespace maths {
		struct vec3 {
			float x, y, z;
			vec3() {
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
			}
			vec3(const float& x, const float& y, const float& z) {
				this->x = x;
				this->y = y;
				this->z = z;
			}
			vec3& add(const vec3& other) {
				x += other.x;
				y += other.y;
				z += other.z;
				return *this;
			}
			vec3& subtract(const vec3& other) {
				x -= other.x;
				y -= other.y;
				z -= other.z;
				return *this;
			}
			vec3& multiply(const vec3& other) {
				x *= other.x;
				y *= other.y;
				z *= other.z;
				return *this;
			}
			vec3& divide(const vec3& other) {
				x /= other.x;
				y /= other.y;
				y /= other.y;
				return *this;
			}
			friend vec3& operator+(vec3 left, const vec3& right) {
				return left.add(right);
			}
			friend vec3& operator-(vec3 left, const vec3& right) {
				return left.subtract(right);
			}
			friend vec3& operator*(vec3 left, const vec3& right) {
				return left.multiply(right);
			}
			friend vec3& operator/(vec3 left, const vec3& right) {
				return left.divide(right);
			}
			vec3& operator+=(const vec3& other) {
				return add(other);
			}
			vec3& operator-=(const vec3& other) {
				return subtract(other);
			}
			vec3& operator*=(const vec3& other) {
				return multiply(other);
			}
			vec3& operator/=(const vec3& other) {
				return divide(other);
			}
			bool operator==(const vec3& other) {
				return x == other.x && y == other.y && z == other.z;
			}
			bool operator!=(const vec3& other) {
				return !(*this == other);
			}
			friend std::ostream& operator<<(std::ostream& stream, const vec3& vector) {
				stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
				return stream;
			}
				
		};
	}
}