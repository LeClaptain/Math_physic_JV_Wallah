//
// Created by theo on 02/09/2024.
//

#pragma once

#include <string>
#ifndef IGNORE_GLM
#include <glm/vec3.hpp>
#endif
#include <string>

namespace maths {
    //Class is named vec3 and is from maths, not to be confused with glm::vec3 :)
    class vec3 {
    public:
        vec3();

        vec3(float v);

        vec3(float x, float y, float z);

        vec3(const vec3 &other);

#ifndef IGNORE_GLM
        vec3(const glm::vec3 &other);
#endif

        // op against other vec3
        vec3 &operator=(const vec3 &other);

        bool operator==(const vec3 &other) const;
        
        bool operator!=(const vec3 &other) const;

        vec3 operator+(const vec3 &other) const;

        vec3 operator-(const vec3 &other) const;

        vec3 operator-() const;

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

        // op against mat3
        vec3 operator*(const mat3& other);

        float dot(const vec3 &other) const;

        vec3 cross(const vec3 &other) const;

        float magnitude() const;

        vec3 normalized() const;

        vec3 &normalize();

        vec3 reflect(const vec3 &normal) const;

        float operator[](const int &index) const;

        float distance(const vec3 &other) const;

        float x() const;

        float y() const;

        float z() const;

#ifndef IGNORE_GLM
        operator glm::vec3() const; //Allows to be converted to a glm::vec3 when necessary (ex : function call)
#endif
        
        operator std::string() const;

        float _x, _y, _z;
    };
} // maths
