#include "vec4.h"
#include <stdexcept>

namespace maths {
	vec4::vec4() : vec4(0)
	{
	}

	vec4::vec4(float v)
	{
		_x = v;
		_y = v;
		_z = v;
		_w = v;
	}

	vec4::vec4(float x, float y, float z, float w)
	{
		_x = x;
		_y = y;
		_z = z;
		_w = w;
	}

	vec4::vec4(const vec4& other)
	{
		_x = other._x;
		_y = other._y;
		_z = other._z;
		_w = other._w;
	}

	vec4::vec4(const vec3& other, float w)
	{
		_x = other.x();
		_y = other.y();
		_z = other.z();
		_w = w;
	}

#ifndef IGNORE_GLM
	vec4::vec4(const glm::vec4& other)
	{
		_x = other.x;
		_y = other.y;
		_z = other.z;
		_w = other.w;
	}
#endif

	float vec4::operator[](const int& index) const
	{
		switch (index)
		{
		case 0:
			return _x;
		case 1:
			return _y;
		case 2:
			return _z;
		case 3:
			return _w;
		default:
			throw std::out_of_range("Index out of range");
		}
	}

	float vec4::x() const
	{
		return _x;
	}

	float vec4::y() const
	{
		return _y;
	}

	float vec4::z() const
	{
		return _z;
	}

	float vec4::w() const
	{
		return _w;
	}

	vec4::operator std::string() const
	{
		return "(" + std::to_string(_x) + ", " + std::to_string(_y) + ", " + std::to_string(_z) + ", " + std::to_string(_w) + ")";
	}

	float vec4::dot(const vec4& other) const
	{
		return _x * other._x + _y * other._y + _z * other._z + _w * other._w;
	}

	float vec4::magnitude() const
	{
		return sqrt(_x * _x + _y * _y + _z * _z + _w * _w);
	}

	vec4 vec4::normalized() const
	{
		return *this / magnitude();
	}

	vec4& vec4::normalize()
	{
		*this /= magnitude();
		return *this;
	}

	float vec4::distance(const vec4& other) const
	{
		return (other - *this).magnitude();
	}

	vec3 vec4::toVec3()
	{
		return vec3(_x, _y, _z);
	}

	vec4 vec4::operator+(const float& other) const
	{
		return vec4(_x + other, _y + other, _z + other, _w + other);
	}

	vec4 vec4::operator-(const float& other) const
	{
		return vec4(_x - other, _y - other, _z - other, _w - other);
	}

	vec4 vec4::operator*(const float& other) const
	{
		return vec4(_x * other, _y * other, _z * other, _w * other);
	}

	vec4 vec4::operator/(const float& other) const
	{
		return vec4(_x / other, _y / other, _z / other, _w / other);
	}

	vec4& vec4::operator+=(const float& other)
	{
		_x += other;
		_y += other;
		_z += other;
		_w += other;

		return *this;
	}

	vec4& vec4::operator-=(const float& other)
	{
		_x -= other;
		_y -= other;
		_z -= other;
		_w -= other;

		return *this;
	}

	vec4& vec4::operator*=(const float& other)
	{
		_x *= other;
		_y *= other;
		_z *= other;
		_w *= other;

		return *this;
	}

	vec4& vec4::operator/=(const float& other)
	{
		_x /= other;
		_y /= other;
		_z /= other;
		_w /= other;

		return *this;
	}

	vec4& vec4::operator=(const vec4& other)
	{
		// Guard self assignment
		if (this == &other)
			return *this;

		_x = other._x;
		_y = other._y;
		_z = other._z;
		_w = other._w;

		return *this;
	}

	bool vec4::operator==(const vec4& other) const
	{
		return _x == other._x && _y == other._y && _z == other._z && _w == other._w;
	}

	bool vec4::operator!=(const vec4& other) const
	{
		return _x != other._x || _y != other._y || _z != other._z || _w != other._w;
	}

	vec4 vec4::operator+(const vec4& other) const
	{
		return vec4(_x + other._x, _y + other._y, _z + other._z, _w + other._w);
	}

	vec4 vec4::operator-(const vec4& other) const
	{
		return vec4(_x - other._x, _y - other._y, _z - other._z, _w - other._w);
	}

	vec4 vec4::operator-() const
	{
		return vec4(-_x, -_y, -_z, -_w);
	}

	vec4& vec4::operator+=(const vec4& other)
	{
		_x += other._x;
		_y += other._y;
		_z += other._z;
		_w += other._w;

		return *this;
	}

	vec4& vec4::operator-=(const vec4& other)
	{
		_x -= other._x;
		_y -= other._y;
		_z -= other._z;
		_w -= other._w;

		return *this;
	}

#ifndef IGNORE_GLM
	vec4::operator glm::vec4() const
	{
		return { _x, _y, _z, _w };
	}
#endif
}

