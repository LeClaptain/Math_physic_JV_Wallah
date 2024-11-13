//
// Created by theo on 02/09/2024.
//

#pragma once
#include "vec3.h"
#include <stdexcept>


namespace maths {
    class mat3 {
    public:
        mat3();

        explicit mat3(const float &v);

        mat3(float m11, float m12, float m13, 
             float m21, float m22, float m23, 
             float m31, float m32, float m33);

        mat3(const mat3 &other);

        // op against other mat
        mat3 &operator=(const mat3 &other);

        bool operator==(const mat3 &other) const;

        mat3 operator+(const mat3 &other) const;

        mat3 operator-(const mat3 &other) const;

        mat3 operator*(const mat3 &other) const;

        mat3 operator-() const;

        mat3 &operator+=(const mat3 &other);

        mat3 &operator-=(const mat3 &other);

        mat3 &operator*=(const mat3 &other);

        // op against float
        mat3 operator+(const float &other) const;

        mat3 operator-(const float &other) const;

        mat3 operator*(const float &other) const;

        mat3 &operator+=(const float &other);

        mat3 &operator-=(const float &other);

        mat3 &operator*=(const float &other);

        mat3 &operator/=(const float &other);

        // op against vec
        vec3 operator*(const vec3 &other) const;

        mat3 transpose() const;

        mat3 inverse() const;

        float det() const;

        static mat3 identity();

        static mat3 fromAxisAngle(const vec3 &axis, float angle);

        static mat3 scale(const vec3 &scale);

        static mat3 scale(const float &scale);

        float operator[](const int &index) const;

    private:
        // COLUMN MAJOR
        /*
         * 1 4 7
         * 2 5 8
         * 3 6 9
         */
        float m[9]{};
    };
}
