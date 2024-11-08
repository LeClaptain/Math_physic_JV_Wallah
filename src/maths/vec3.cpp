//
// Created by theo on 02/09/2024.
//

#include "vec3.h"

#include <cmath>
#include <stdexcept>
#include <string>
#include "mat3.h"

namespace maths
{
	vec3::vec3() : vec3(0)
	{
	}

	vec3::vec3(float v)
	{
		_x = _y = _z = v;
	}

	vec3::vec3(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	vec3::vec3(const vec3& other)
	{
		_x = other._x;
		_y = other._y;
		_z = other._z;
	}

#ifndef IGNORE_GLM
	vec3::vec3(const glm::vec3& other)
	{
		_x = other.x;
		_y = other.y;
		_z = other.z;
	}
#endif

	// op against other vec3
	vec3& vec3::operator=(const vec3& other)
	{
		// Guard self assignment
		if (this == &other)
			return *this;

		_x = other._x;
		_y = other._y;
		_z = other._z;

		return *this;
	}

	bool vec3::operator==(const vec3& other) const
	{
		return _x == other._x && _y == other._y && _z == other._z;
	}

	bool vec3::operator!=(const vec3& other) const
	{
		return _x != other._x || _y != other._y || _z != other._z;
	}

	vec3 vec3::operator+(const vec3& other) const
	{
		return vec3(_x + other._x, _y + other._y, _z + other._z);
	}

	vec3 vec3::operator-(const vec3& other) const
	{
		return vec3(_x - other._x, _y - other._y, _z - other._z);
	}

	vec3 vec3::operator-() const
	{
		return vec3(-_x, -_y, -_z);
	}

	vec3& vec3::operator+=(const vec3& other)
	{
		_x += other._x;
		_y += other._y;
		_z += other._z;

		return *this;
	}

	vec3& vec3::operator-=(const vec3& other)
	{
		_x -= other._x;
		_y -= other._y;
		_z -= other._z;

		return *this;
	}

	// op against float
	vec3 vec3::operator+(const float& other) const
	{
		return vec3(_x + other, _y + other, _z + other);
	}

	vec3 vec3::operator-(const float& other) const
	{
		return vec3(_x - other, _y - other, _z - other);
	}

	vec3 vec3::operator*(const float& other) const
	{
		return vec3(_x * other, _y * other, _z * other);
	}

	vec3 vec3::operator/(const float& other) const
	{
		return vec3(_x / other, _y / other, _z / other);
	}

	vec3& vec3::operator+=(const float& other)
	{
		_x += other;
		_y += other;
		_z += other;

		return *this;
	}

	vec3& vec3::operator-=(const float& other)
	{
		_x -= other;
		_y -= other;
		_z -= other;

		return *this;
	}

	vec3& vec3::operator*=(const float& other)
	{
		_x *= other;
		_y *= other;
		_z *= other;

		return *this;
	}

	vec3& vec3::operator/=(const float& other)
	{
		_x /= other;
		_y /= other;
		_z /= other;

		return *this;
	}

	float vec3::dot(const vec3& other) const
	{
		return _x * other._x + _y * other._y + _z * other._z;
	}

	vec3 vec3::cross(const vec3& other) const
	{
		return vec3(_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
	}

	float vec3::magnitude() const
	{
		return sqrt(_x * _x + _y * _y + _z * _z);
	}

	vec3 vec3::normalized() const
	{
		return *this / magnitude();
	}

	vec3& vec3::normalize()
	{
		*this /= magnitude();
		return *this;
	}

	vec3 vec3::reflect(const vec3& normal) const
	{
		return *this - normal * 2.0f * dot(normal);
	}

	float vec3::operator[](const int& index) const
	{
		switch (index)
		{
		case 0:
			return _x;
		case 1:
			return _y;
		case 2:
			return _z;
		default:
			throw std::out_of_range("Index out of range");
		}
	}

	float vec3::distance(const vec3& other) const
	{
		return (other - *this).magnitude();
	}


	float vec3::x() const
	{
		return _x;
	}

	float vec3::y() const
	{
		return _y;
	}

	float vec3::z() const
	{
		return _z;
	}

#ifndef IGNORE_GLM
	vec3::operator glm::vec3() const
	{
		return {_x, _y, _z};
	}
#endif

	vec3::operator std::string() const
	{
		return "(" +std::to_string(_x) + ", " + std::to_string(_y) + ", " + std::to_string(_z) + ")";
	}
} // maths
