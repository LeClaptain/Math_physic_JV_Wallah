#include "mat4.h"
#include "mat3.h"

namespace maths {

	maths::mat4::mat4() : mat4(0)
	{
	}

	mat4::mat4(const float& v)
	{
		for(float& i : m)
		{
			i = v;
		}
	}

	mat4::mat4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
	{
		m[0] = m11;
		m[1] = m21;
		m[2] = m31;
		m[3] = m41;
		m[4] = m12;
		m[5] = m22;
		m[6] = m32;
		m[7] = m42;
		m[8] = m13;
		m[9] = m23;
		m[10] = m33;
		m[11] = m43;
		m[12] = m14;
		m[13] = m24;
		m[14] = m34;
		m[15] = m44;
	}

	mat4::mat4(const mat4& other)
	{
		for (int i = 0; i < 16; i++)
		{
			m[i] = other.m[i];
		}
	}

	float mat4::operator[](const int& index) const
	{
		return m[index];
	}

	mat4& mat4::operator=(const mat4& other)
	{
		// Guard self assignment
		if (this == &other)
			return *this;

		for (int i = 0; i < 16; i++)
		{
			m[i] = other.m[i];
		}

		return *this;
	}

	bool mat4::operator==(const mat4& other) const
	{
		for (int i = 0; i < 16; i++)
		{
			if (m[i] != other.m[i])
			{
				return false;
			}
		}

		return true;
	}

	mat4 mat4::operator+(const mat4& other) const
	{
		mat4 res(other);

		for (int i = 0; i < 16; i++)
		{
			res.m[i] += m[i];
		}

		return res;
	}

	mat4 mat4::operator-(const mat4& other) const
	{
		mat4 res(other);

		for (int i = 0; i < 9; i++)
		{
			res.m[i] -= m[i];
		}

		return res;
	}

	mat4 mat4::operator*(const mat4& other) const
	{
		mat4 result(m[0]*other[0]+m[4]*other[1]+m[8]*other[2]+m[12]*other[3], m[0]*other[4]+m[4]*other[5]+m[8]*other[6]+m[12]*other[7], m[0]*other[8]+m[4]*other[9]+m[8]*other[10]+m[12]*other[11], m[0]*other[12]+m[4]*other[13]+m[8]*other[14]+m[12]*other[15],
					m[1]*other[0]+m[5]*other[1]+m[9]*other[2]+m[13]*other[3], m[1]*other[4]+m[5]*other[5]+m[9]*other[6]+m[13]*other[7], m[1]*other[8]+m[5]*other[9]+m[9]*other[10]+m[13]*other[11], m[1]*other[12]+m[5]*other[13]+m[9]*other[14]+m[13]*other[15],
					m[2]*other[0]+m[6]*other[1]+m[10]*other[2]+m[14]*other[3], m[2]*other[4]+m[6]*other[5]+m[10]*other[6]+m[14]*other[7], m[2]*other[8]+m[6]*other[9]+m[10]*other[10]+m[14]*other[11], m[2]*other[12]+m[6]*other[13]+m[10]*other[14]+m[14]*other[15],
					m[3]*other[0]+m[7]*other[1]+m[11]*other[2]+m[15]*other[3], m[3]*other[4]+m[7]*other[5]+m[11]*other[6]+m[15]*other[7], m[3]*other[8]+m[7]*other[9]+m[11]*other[10]+m[15]*other[11], m[3]*other[12]+m[7]*other[13]+m[11]*other[14]+m[15]*other[15]);
		
		return result;
	}

	mat4 mat4::operator-() const
	{
		mat4 res(*this);

		for (float& i : res.m)
		{
			i *= -1.f;
		}

		return res;
	}

	mat4& mat4::operator+=(const mat4& other)
	{
		for (int i = 0; i < 16; i++)
		{
			m[i] += other.m[i];
		}

		return *this;
	}

	mat4& mat4::operator-=(const mat4& other)
	{
		for (int i = 0; i < 16; i++)
		{
			m[i] -= other.m[i];
		}

		return *this;
	}

	mat4& mat4::operator*=(const mat4& other)
	{
		float temp[16] = {
			m[0] * other.m[0] + m[4] * other.m[1] + m[8] * other.m[2] + m[12] * other.m[3],
			m[1] * other.m[0] + m[5] * other.m[1] + m[9] * other.m[2] + m[13] * other.m[3],
			m[2] * other.m[0] + m[6] * other.m[1] + m[10] * other.m[2] + m[14] * other.m[3],
			m[3] * other.m[0] + m[7] * other.m[1] + m[11] * other.m[2] + m[15] * other.m[3],

			m[0] * other.m[4] + m[4] * other.m[5] + m[8] * other.m[6] + m[12] * other.m[7],
			m[1] * other.m[4] + m[5] * other.m[5] + m[9] * other.m[6] + m[13] * other.m[7],
			m[2] * other.m[4] + m[6] * other.m[5] + m[10] * other.m[6] + m[14] * other.m[7],
			m[3] * other.m[4] + m[7] * other.m[5] + m[11] * other.m[6] + m[15] * other.m[7],

			m[0] * other.m[8] + m[4] * other.m[9] + m[8] * other.m[10] + m[12] * other.m[11],
			m[1] * other.m[8] + m[5] * other.m[9] + m[9] * other.m[10] + m[13] * other.m[11],
			m[2] * other.m[8] + m[6] * other.m[9] + m[10] * other.m[10] + m[14] * other.m[11],
			m[3] * other.m[8] + m[7] * other.m[9] + m[11] * other.m[10] + m[15] * other.m[11],

			m[0] * other.m[12] + m[4] * other.m[13] + m[8] * other.m[14] + m[12] * other.m[15],
			m[1] * other.m[12] + m[5] * other.m[13] + m[9] * other.m[14] + m[13] * other.m[15],
			m[2] * other.m[12] + m[6] * other.m[13] + m[10] * other.m[14] + m[14] * other.m[15],
			m[3] * other.m[12] + m[7] * other.m[13] + m[11] * other.m[14] + m[15] * other.m[15]
		};

		for (int i = 0; i < 16; ++i) {
			m[i] = temp[i];
		}

		return *this;
	}

	mat4 mat4::operator+(const float& other) const
	{
		mat4 result(*this);

		for (float& i : result.m)
		{
			i += other;
		}

		return result;
	}

	mat4 mat4::operator-(const float& other) const
	{
		mat4 result(*this);

		for (float& i : result.m)
		{
			i -= other;
		}

		return result;
	}

	mat4 mat4::operator*(const float& other) const
	{
		mat4 result(*this);

		for (float& i : result.m)
		{
			i *= other;
		}

		return result;
	}

	mat4 mat4::operator/(const float& other) const
	{
		mat4 result(*this);

		for (float& i : result.m)
		{
			i /= other;
		}

		return result;
	}

	mat4& mat4::operator+=(const float& other)
	{
		for (int i = 0; i < 16; i++)
		{
			m[i] += other;
		}

		return *this;
	}

	mat4& mat4::operator-=(const float& other)
	{
		for (int i = 0; i < 16; i++)
		{
			m[i] -= other;
		}

		return *this;
	}

	mat4& mat4::operator*=(const float& other)
	{
		for (int i = 0; i < 16; i++)
		{
			m[i] *= other;
		}

		return *this;
	}

	mat4& mat4::operator/=(const float& other)
	{
		for (int i = 0; i < 16; i++)
		{
			m[i] /= other;
		}

		return *this;
	}

	vec4 mat4::operator*(const vec4& other) const
	{
		float x, y, z, w;

		x = m[0] * other[0] + m[4] * other[1] + m[8] * other[2] + m[12] * other[3];
		y = m[1] * other[0] + m[5] * other[1] + m[9] * other[2] + m[13] * other[3];
		z = m[2] * other[0] + m[6] * other[1] + m[10] * other[2] + m[14] * other[3];
		w = m[3] * other[0] + m[7] * other[1] + m[11] * other[2] + m[15] * other[3];

		return vec4(x, y, z, w);
	}

	mat4 mat4::transpose() const
	{
		return mat4(m[0],  m[1],  m[2],  m[3],
					m[4],  m[5],  m[6],  m[7],
					m[8],  m[9],  m[10], m[11],
					m[12], m[13], m[14], m[15]);
	}

	float mat4::det() const
	{
		float res = m[0] * mat3(m[5], m[9],  m[13],
								m[6], m[10], m[14],
								m[7], m[11], m[15]).det()
			+
					m[4] * mat3(m[1], m[9],  m[13],
								m[2], m[10], m[14],
								m[3], m[11], m[15]).det()
			+
					m[8] * mat3(m[1], m[5],  m[13],
								m[2], m[6],  m[14],
								m[3], m[7],  m[15]).det()
			+
					m[12] * mat3(m[1], m[5],  m[9],
								 m[2], m[6],  m[10],
								 m[3], m[7],  m[11]).det();
		
		return res;
	}

	mat4 mat4::identity()
	{
		return mat4(1.0, 0.0, 0.0, 0.0,
					0.0, 1.0, 0.0, 0.0,
					0.0, 0.0, 1.0, 0.0,
					0.0, 0.0, 0.0, 1.0);
	}
}

