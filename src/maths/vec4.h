#pragma once

#include <string>
#ifndef IGNORE_GLM
#include <glm/vec4.hpp>
#endif
#include "vec3.h"

namespace maths {
	class vec4
	{
	public:
		vec4();

		vec4(float v);

		vec4(float x, float y, float z, float w);

		vec4(const vec4& other);

		vec4(const vec3& other, float w);

#ifndef IGNORE_GLM
		vec4(const glm::vec4& other);
#endif
		float operator[](const int& index) const;

		float x() const;

		float y() const;

		float z() const;

		float w() const;

#ifndef IGNORE_GLM
		operator glm::vec4() const;
#endif

		operator std::string() const;

		float dot(const vec4& other) const;

		float magnitude() const;

		vec4 normalized() const;

		vec4& normalize();

		float distance(const vec4& other) const;

		vec3 toVec3();

		// op against float
		vec4 operator+(const float& other) const;

		vec4 operator-(const float& other) const;

		vec4 operator*(const float& other) const;

		vec4 operator/(const float& other) const;

		vec4& operator+=(const float& other);

		vec4& operator-=(const float& other);

		vec4& operator*=(const float& other);

		vec4& operator/=(const float& other);

		// op against other vec4
		vec4& operator=(const vec4& other);

		bool operator==(const vec4& other) const;

		bool operator!=(const vec4& other) const;

		vec4 operator+(const vec4& other) const;

		vec4 operator-(const vec4& other) const;

		vec4 operator-() const;

		vec4& operator+=(const vec4& other);

		vec4& operator-=(const vec4& other);

	private:
		float _x, _y, _z, _w;
	};
}

