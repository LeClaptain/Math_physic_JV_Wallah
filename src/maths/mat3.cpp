//
// Created by theo on 02/09/2024.
//

#include <maths/mat3.h>

namespace maths
{
	mat3::mat3() : mat3(0)
	{
	}

	mat3::mat3(const float& v)
	{
		for (float& i : m)
		{
			i = v;
		}
	}

	mat3::mat3(const float m11, const float m12, const float m13, const float m21, const float m22, const float m23,
	           const float m31, const float m32, const float m33)
	{
		m[0] = m11;
		m[1] = m21;
		m[2] = m31;
		m[3] = m12;
		m[4] = m22;
		m[5] = m32;
		m[6] = m13;
		m[7] = m23;
		m[8] = m33;
	}

	mat3::mat3(const mat3& other)
	{
		for (int i = 0; i < 9; i++)
		{
			m[i] = other.m[i];
		}
	}

	float mat3::det() const
	{
		return m[0] * m[4] * m[8] + m[3] * m[7] * m[2] + m[6] * m[1] * m[5] - m[0] * m[7] * m[5] - m[3] * m[1] * m[8] -
			m[6] * m[4] * m[2];
	}

	mat3& mat3::operator=(const mat3& other)
	{
		// Guard self assignment
		if (this == &other)
			return *this;

		for (int i = 0; i < 9; i++)
		{
			m[i] = other.m[i];
		}

		return *this;
	}

	bool mat3::operator==(const mat3& other) const
	{
		for (int i = 0; i < 9; i++)
		{
			if (m[i] != other.m[i])
			{
				return false;
			}
		}

		return true;
	}

	mat3 mat3::operator+(const mat3& other) const
	{
		mat3 res(other);

		for (int i = 0; i < 9; i++)
		{
			res.m[i] += m[i];
		}

		return res;
	}

	mat3 mat3::operator-(const mat3& other) const
	{
		mat3 res(other);

		for (int i = 0; i < 9; i++)
		{
			res.m[i] -= m[i];
		}

		return res;
	}

	mat3 mat3::operator*(const mat3& other) const
	{
		mat3 result;

		// Probqbly trash
		for (int col = 0; col < 3; col++)
		{
			for (int row = 0; row < 3; row++)
			{
				float sum = 0.0f;
				for (int k = 0; k < 3; ++k)
				{
					sum += m[col * 3 + k] * other.m[k * 3 + row];
				}
				result.m[col * 3 + row] = sum;
			}
		}

		return result;
	}

	mat3 mat3::operator-() const
	{
		mat3 res(*this);

		for (float& i : res.m)
		{
			i *= -1.f;
		}

		return res;
	}

	mat3& mat3::operator+=(const mat3& other)
	{
		for (int i = 0; i < 9; i++)
		{
			m[i] += other.m[i];
		}

		return *this;
	}

	mat3& mat3::operator-=(const mat3& other)
	{
		for (int i = 0; i < 9; i++)
		{
			m[i] -= other.m[i];
		}

		return *this;
	}

	mat3& mat3::operator*=(const mat3& other)
	{
		mat3 result;

		// Probqbly trash
		for (int col = 0; col < 3; col++)
		{
			for (int row = 0; row < 3; row++)
			{
				float sum = 0.0f;
				for (int k = 0; k < 3; ++k)
				{
					sum += m[col * 3 + k] * other.m[k * 3 + row];
				}
				result.m[col * 3 + row] = sum;
			}
		}

		*this = result;

		return *this;
	}

	mat3 mat3::operator+(const float& other) const
	{
		mat3 result(*this);

		for (float& i : result.m)
		{
			i += other;
		}

		return result;
	}

	mat3 mat3::operator-(const float& other) const
	{
		mat3 result(*this);

		for (float& i : result.m)
		{
			i -= other;
		}

		return result;
	}

	mat3 mat3::operator*(const float& other) const
	{
		mat3 result(*this);

		for (float& i : result.m)
		{
			i *= other;
		}

		return result;
	}

	mat3& mat3::operator+=(const float& other)
	{
		for (int i = 0; i < 9; i++)
		{
			m[i] += other;
		}

		return *this;
	}

	mat3& mat3::operator-=(const float& other)
	{
		for (int i = 0; i < 9; i++)
		{
			m[i] -= other;
		}

		return *this;
	}

	mat3& mat3::operator*=(const float& other)
	{
		for (int i = 0; i < 9; i++)
		{
			m[i] *= other;
		}

		return *this;
	}

	mat3& mat3::operator/=(const float& other)
	{
		for (int i = 0; i < 9; i++)
		{
			m[i] /= other;
		}

		return *this;
	}

	vec3 mat3::operator*(const vec3& other) const
	{
		return {};
	}


	mat3 mat3::transpose() const
	{
		mat3 res;

		res.m[0] = m[0];
		res.m[1] = m[3];
		res.m[2] = m[6];
		res.m[3] = m[1];
		res.m[4] = m[4];
		res.m[5] = m[7];
		res.m[6] = m[2];
		res.m[7] = m[5];
		res.m[8] = m[8];

		return res;
	}

	mat3 mat3::inverse() const
	{
		// TODO
		return mat3();
	}

	mat3 mat3::identity()
	{
		return mat3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}
} // maths
