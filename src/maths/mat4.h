#pragma once

#include "vec4.h"

namespace maths {
	class mat4
	{
	public:
		mat4();

		explicit mat4(const float& v);

		mat4(float m11, float m12, float m13, float m14, 
			 float m21, float m22, float m23, float m24, 
			 float m31, float m32, float m33, float m34, 
			 float m41, float m42, float m43, float m44);

		mat4(const mat4& other);

		float operator[](const int& index) const;

        // op against other mat
        mat4& operator=(const mat4& other);

        bool operator==(const mat4& other) const;

        mat4 operator+(const mat4& other) const;

        mat4 operator-(const mat4& other) const;

        mat4 operator*(const mat4& other) const;

        mat4 operator-() const;

        mat4& operator+=(const mat4& other);

        mat4& operator-=(const mat4& other);

        mat4& operator*=(const mat4& other);

        // op against float
        mat4 operator+(const float& other) const;

        mat4 operator-(const float& other) const;

        mat4 operator*(const float& other) const;

        mat4 operator/(const float& other) const;

        mat4& operator+=(const float& other);

        mat4& operator-=(const float& other);

        mat4& operator*=(const float& other);

        mat4& operator/=(const float& other);

        // op against vec
        vec4 operator*(const vec4& other) const;

        mat4 transpose() const;

        float det() const;

        static mat4 identity();

	private:
		// still COLUMN MAJOR
		/*
		 * 0 4  8 12
		 * 1 5  9 13
		 * 2 6 10 14
		 * 3 7 11 15
		 */
		float m[16]{};
	};
}

