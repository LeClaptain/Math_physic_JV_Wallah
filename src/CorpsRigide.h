#pragma once
#include "maths/mat3.h"
#include "maths/mat4.h"
#include "maths/vec3.h"
#include "maths/vec4.h"
#include "maths/Quaternion.h"

using namespace maths;

class CorpsRigide
{
public:
    double getMass() const { return mass; }
    void setMass(double mass) { this->mass = mass; }

    double getOneOverMass() const { return 1.0 / mass; }

    vec3 getPosition() const { return position; }
    void setPosition(const vec3& position) { this->position = position; }

    vec3 getExtent() const { return extent; }
    void setExtent(const vec3& extent) { this->extent = extent; }

    quaternion getOrientation() const { return orientation; }
    void setOrientation(quaternion orientation) { this->orientation = orientation; }

    vec3 getAngularVelocity() const { return angularVelocity; }
    void setAngularVelocity(const vec3& angularVelocity) { this->angularVelocity = angularVelocity; }

    vec3 getAngularAcceleration() const { return angularAcceleration; }
    void setAngularAcceleration(const vec3& angularAcceleration) { this->angularAcceleration = angularAcceleration; }

    mat3 getJminusOne() const { return JminusOne; }
    void setJminusOne(const mat3& JminusOne) { this->JminusOne = JminusOne; }

    vec3 getVelocity() const { return velocity; }
    void setVelocity(const vec3& velocity) { this->velocity = velocity; }

    vec3 getAcceleration() const { return acceleration; }
    void setAcceleration(const vec3& acceleration) { this->acceleration = acceleration; }

    vec3 getForces() const { return forces; }
    void setForces(const vec3& forces) { this->forces = forces; }

    // Before physics
    void update(double dt);
    void draw();

private:
    double mass;
    vec3 position;
    vec3 extent{1, 1, 1};

    // angular
    quaternion orientation;
    vec3 angularVelocity;
    vec3 angularAcceleration;
    mat3 JminusOne;

    // linear
    vec3 velocity;
    vec3 acceleration;
    vec3 forces;
};
