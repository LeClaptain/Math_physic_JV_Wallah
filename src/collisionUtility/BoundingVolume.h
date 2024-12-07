#pragma once

#include "../maths/vec3.h"
#include "ofColor.h"
#include "../CorpsRigides/CorpsRigide.h"

class BoundingVolume
{
public:
    BoundingVolume(CorpsRigide* rb);

    BoundingVolume(float size, vec3 position)
    {
        radius = size;
        center = position;
    }

    float getRadius() { return radius; }
    vec3 getCenter() { return center; }
    CorpsRigide* getRigidBody() { return rigidbody; }
    void setRigidBody(CorpsRigide* newBody) { rigidbody = newBody; }

    void draw(ofColor color = ofColor(255, 0, 0));

private:
    float radius;
    vec3 center; // need to update bounding volume center to follow rigidbody
    CorpsRigide* rigidbody;
};
