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

#ifndef IGNORE_GLM
	vec4::vec4(const glm::vec4& other)
	{
		_x = other.x;
		_y = other.y;
		_z = other.z;
		_w = other.w;
	}
#endif

	float maths::vec4::operator[](const int& index) const
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
}

