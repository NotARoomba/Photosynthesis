#pragma once
#include <iostream>

namespace photosynthesis {
	namespace maths {
		struct vec4 {
			float x, y, z, w;
			vec4() {
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
				w = 0.0f;
			}
			vec4(const float& x, const float& y, const float& z, const float& w) {
				this->x = x;
				this->y = y;
				this->z = z;
				this->w = w;
			}
			vec4& add(const vec4& other) {
				x += other.x;
				y += other.y;
				z += other.z;
				w += other.w;
				return *this;
			}
			vec4& subtract(const vec4& other) {
				x -= other.x;
				y -= other.y;
				z -= other.z;
				w -= other.w;
				return *this;
			}
			vec4& multiply(const vec4& other) {
				x *= other.x;
				y *= other.y;
				z *= other.z;
				w *= other.w;
				return *this;
			}
			vec4& divide(const vec4& other) {
				x /= other.x;
				y /= other.y;
				y /= other.y;
				w /= other.w;
				return *this;
			}
			friend vec4& operator+(vec4 left, const vec4& right) {
				return left.add(right);
			}
			friend vec4& operator-(vec4 left, const vec4& right) {
				return left.subtract(right);
			}
			friend vec4& operator*(vec4 left, const vec4& right) {
				return left.multiply(right);
			}
			friend vec4& operator/(vec4 left, const vec4& right) {
				return left.divide(right);
			}
			vec4& operator+=(const vec4& other) {
				return add(other);
			}
			vec4& operator-=(const vec4& other) {
				return subtract(other);
			}
			vec4& operator*=(const vec4& other) {
				return multiply(other);
			}
			vec4& operator/=(const vec4& other) {
				return divide(other);
			}
			bool operator==(const vec4& other) {
				return x == other.x && y == other.y && z == other.z && w == other.w;
			}
			bool operator!=(const vec4& other) {
				return !(*this == other);
			}
			friend std::ostream& operator<<(std::ostream& stream, const vec4& vector) {
				stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
				return stream;
			}

		};
	}
}