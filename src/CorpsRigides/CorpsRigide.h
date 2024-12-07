#pragma once
#include "of3dPrimitives.h"
#include "../maths/mat3.h"
#include "../maths/mat4.h"
#include "../maths/vec3.h"
#include "../maths/vec4.h"
#include "../maths/Quaternion.h"
#include "ofMaterial.h"

using namespace maths;

class CorpsRigide
{
public:
    CorpsRigide(vec3 extent, vec3 position, ofColor color);

    virtual ~CorpsRigide() = default;

    double getMass() const { return mass; }

    void setMass(double mass)
    {
        this->mass = mass;
        inverseMass = 1.0 / mass;
        calcJminusOne();
    }

    double getOneOverMass() const { return inverseMass; }

    vec3 getPosition() const { return position; }
    void setPosition(const vec3& position) { this->position = position; }

    virtual vec3 getExtent() const { return extent; }

    virtual void setExtent(const vec3& extent)
    {
        this->extent = extent;
        calcJminusOne();
    }

    quaternion getOrientation() const { return orientation; }
    void setOrientation(quaternion orientation) { this->orientation = orientation.normalized(); }

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
    void addForce(vec3 f) { forces += f; }

    bool getunmoovable() const { return unmoovable; }
    void setUnmoovable(bool newValue) { this->unmoovable = newValue; }

    void addForce(const vec3& force, const vec3& point)
    {
        tau += point.cross(force);
        forces += force;
    }

    float getInverseMass() const { return inverseMass; }
    vec3 getTau() const { return tau; }
    void setTau(const vec3& tau) { this->tau = tau; }

    virtual void draw() = 0;
    virtual of3dPrimitive* getRigidBody() = 0;

    float getContainingRadius() const
    {
        return (extent / 2).magnitude();
    }

    ofColor color;
    ofMaterial material;

private:
    // Calcule la matrice d'inertie inverse
    void calcJminusOne()
    {
        // dans le cas d'un parallélépipède, on definis un axe (c) comme etant la hauteur.
        // cet axe sera ignore dans le calcul de la matrice.
        // on trie donc l'extent pour trouver c et n'utiliser que a et b
        float abc[3] = {extent.x(), extent.y(), extent.z()};

        // tri, decroissant
        for (int i = 0; i < 3; i++)
        {
            for (int j = i + 1; j < 3; j++)
            {
                if (abc[i] < abc[j])
                {
                    float temp = abc[i];
                    abc[i] = abc[j];
                    abc[j] = temp;
                }
            }
        }

        JminusOne = 1.f / 12.f * mass * (abc[1] * abc[1] + abc[2] * abc[2]) * mat3::identity();
        JminusOne = JminusOne.inverse();
    }

    double mass = 0.0;
    double inverseMass = 0.0;
    vec3 position;
    vec3 extent{100, 100, 100};

    bool unmoovable = false;

    // angular
    quaternion orientation;
    vec3 tau{0, 0, 0};
    vec3 angularVelocity{0, 0, 0};
    vec3 angularAcceleration{0, 0, 0};
    mat3 JminusOne;

    // linear
    vec3 velocity = vec3(0);
    vec3 acceleration = vec3(0);
    vec3 forces = vec3(0);

    void applyRotationFromQuaternion();
};
