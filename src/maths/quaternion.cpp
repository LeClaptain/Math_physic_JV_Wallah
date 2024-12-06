#include "quaternion.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


using namespace glm;
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
		return mat3(1.f-2.f*(_v.y()*_v.y()+_v.z()*_v.z()), 2.f*(_v.x()*_v.y() + _v.z()*_w),     2.f*(_v.x()*_v.z() - _v.y()*_w),
					2.f*(_v.x()*_v.y() - _v.z()*_w), 	   1.f-2.f*(_v.x()*_v.x()+_v.z()*_v.z()), 2.f*(_v.y()*_v.z()+_v.x()*_w),
					2.f*(_v.x()*_v.z() + _v.y()*_w),     2.f*(_v.y()*_v.z()-_v.x()*_w),       1.f-2.f*(_v.x()*_v.x()+_v.y()*_v.y()));
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

	void quaternion::normalize()
	{
		float m = magnitude();
		_w /= m;
		_v/= m;
	}

	quaternion quaternion::normalized()
	{
		return *this / magnitude();
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
	
	quaternion quaternion::operator+(const quaternion& other) const {
		return quaternion(
			this->_w + other._w,
			this->_v.x() + other._v.x(),
			this->_v.y() + other._v.y(),
			this->_v.z() + other._v.z()
		);
	}

	quaternion quaternion::operator-(const quaternion& other) const
	{
		return other * conjugate();
	}

	quaternion quaternion::operator*(const quaternion& other) const
	{
		return quaternion(_w * other._w - _v.dot(other._v), (other._v * _w + _v * other._w + _v.cross(other._v)));
	}

	quaternion::operator glm::quat() const {
		return glm::quat(_w, _v.x(), _v.y(), _v.z());
	}
}
