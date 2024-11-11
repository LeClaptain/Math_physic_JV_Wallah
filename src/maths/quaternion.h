#pragma once

#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

namespace maths
{
	class quaternion
	{
	public:
		quaternion();

		quaternion(float w, float x, float y, float z);

		quaternion(float w, vec3 v);

		mat4 toMat4();

		mat3 toMat3();

		float magnitude() const;

		quaternion conjugate() const;

		quaternion inverse() const;

		float dot(quaternion other) const;

		quaternion pow(float t) const;

		bool isRotation() const;

		quaternion operator-() const;

		// operations on floats
		quaternion operator+(const float& other) const;

		quaternion operator-(const float& other) const;

		quaternion operator*(const float& other) const;

		quaternion operator/(const float& other) const;

		// op against other quaternions
		quaternion& operator=(const quaternion& other);

		bool operator==(const quaternion& other) const;

		bool operator!=(const quaternion& other) const;

		quaternion operator-(const quaternion& other) const;

		quaternion operator*(const quaternion& other) const;

	private:
		float _w;
		vec3 _v;
	};
}

