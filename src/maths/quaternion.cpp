#include "quaternion.h"

namespace maths {
	quaternion::quaternion()
	{
		_w = 1;
		_v = vec3(0, 0, 0);
	}

	quaternion::quaternion(float w, float x, float y, float z)
	{
		_w = w;
		_v = vec3(x, y, z);
	}

	quaternion::quaternion(float w, vec3 v)
	{
		_w = w;
		_v = v;
	}

	mat4 quaternion::toMat4()
	{
		return mat4(_w,		 -_v.z(), _v.y(),  _v.x(),
					_v.z(),  _w,	  -_v.x(), _v.y(),
					-_v.y(), _v.x(),  _w,	   _v.z(),
					-_v.x(), -_v.y(), -_v.z(), _w);
	}

	mat3 quaternion::toMat3()
	{
		return mat3(1-2*(_v.y()*_v.y()+_v.z()*_v.z()), 2*(_v.x()*_v.y() + _v.z()*_w),     2*(_v.x()*_v.z() - _v.y()*_w),
					2*(_v.x()*_v.y() - _v.z()*_w), 	   1-2*(_v.x()*_v.x()+_v.z()*_v.z()), 2*(_v.y()*_v.z()+_v.x()*_w),
					2*(_v.x()*_v.z() + _v.y()*_w),     2*(_v.y()*_v.z()-_v.x()*_w),       1-2*(_v.x()*_v.x()+_v.y()*_v.y()));
	}

	float quaternion::magnitude() const
	{
		return vec4(_v, _w).magnitude();
	}

	quaternion quaternion::conjugate() const
	{
		return quaternion(_w, -_v);
	}

	quaternion quaternion::inverse() const
	{
		return conjugate() / magnitude();
	}

	float quaternion::dot(quaternion other) const
	{
		return _w * other._w + _v.dot(other._v);
	}

	quaternion quaternion::pow(float t) const
	{
		if (0.99f < _w && _w < 1.01)
		{
			return quaternion(_w, _v);
		}
		float alpha = acos(_w);
		return quaternion(cos(t * alpha), _v * (sin(t * alpha) / sin(alpha)));
	}

	bool quaternion::isRotation() const
	{
		return magnitude() == 1;
	}

	quaternion quaternion::operator-() const
	{
		return quaternion(-_w, -_v);
	}

	quaternion quaternion::operator+(const float& other) const
	{
		return quaternion(_w + other, _v + other);
	}

	quaternion quaternion::operator-(const float& other) const
	{
		return quaternion(_w - other, _v - other);
	}

	quaternion quaternion::operator*(const float& other) const
	{
		return quaternion(_w * other, _v * other);
	}

	quaternion quaternion::operator/(const float& other) const
	{
		return quaternion(_w / other, _v / other);
	}

	quaternion& quaternion::operator=(const quaternion& other)
	{
		if (this == &other)
			return *this;

		_w = other._w;
		_v = other._v;

		return *this;
	}

	bool quaternion::operator==(const quaternion& other) const
	{
		return _w == other._w && _v == other._v;
	}

	bool quaternion::operator!=(const quaternion& other) const
	{
		return _w != other._w || _v != other._v;
	}

	quaternion quaternion::operator-(const quaternion& other) const
	{
		return other * conjugate();
	}

	quaternion quaternion::operator*(const quaternion& other) const
	{
		return quaternion(_w * other._w - _v.dot(other._v), (other._v * _w + _v * other._w + _v.cross(other._v)));
	}
}
