#pragma once
#include "CorpsRigides/CorpsRigide.h"
#include "ofMaterial.h"

class Box : public CorpsRigide
{
public:
    Box(vec3 extent, vec3 position, ofColor color) : CorpsRigide(extent, position, color)
    {
        rigidBody.setPosition(position);
        rigidBody.set(extent.x(), extent.y(), extent.z());
    }

    void draw() override
    {
        material.setDiffuseColor(color);
        material.setSpecularColor(ofColor(100, 100, 100));
        material.setShininess(50);
        material.begin();
        rigidBody.draw();
        material.end();
    }

    of3dPrimitive* getRigidBody() override { return &rigidBody; }

private:
    vec3 extent;
    ofBoxPrimitive rigidBody;
    
};
