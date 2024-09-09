//
// Created by theo on 02/09/2024.
//

#pragma once

#include <glm/vec3.hpp>

namespace maths {
    class vec3 {
    public:
        vec3();

        vec3(float v);

        vec3(float x, float y, float z);

        vec3(const vec3 &other);

        // op against other vec3
        vec3 &operator=(const vec3 &other);

        bool operator==(const vec3 &other);

        vec3 operator+(const vec3 &other);

        vec3 operator-(const vec3 &other);

        vec3 operator-();

        vec3 &operator+=(const vec3 &other);

        vec3 &operator-=(const vec3 &other);

        // op against float
        vec3 operator+(const float &other) const;

        vec3 operator-(const float &other) const;

        vec3 operator*(const float &other) const;

        vec3 operator/(const float &other) const;

        vec3 &operator+=(const float &other);

        vec3 &operator-=(const float &other);

        vec3 &operator*=(const float &other);

        vec3 &operator/=(const float &other);

        float dot(const vec3 &other);

        vec3 cross(const vec3 &other);

        float magnitude();

        vec3 normalized();

        vec3 &normalize();

        vec3 reflect(const vec3 &normal);

        float operator[](const int &index) const;

        float x() const;

        float y() const;

        float z() const;

        operator glm::vec3() const;

        float _x, _y, _z;
    };

    vec3 operator+(const float &lhs, const vec3 &rhs);

    vec3 operator-(const float &lhs, const vec3 &rhs);

    vec3 operator*(const float &lhs, const vec3 &rhs);

    vec3 operator/(const float &lhs, const vec3 &rhs);
} // maths
