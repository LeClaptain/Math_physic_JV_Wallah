#pragma once
#include "CorpsRigides/CorpsRigide.h"
#include "ofMaterial.h"

class Cone : public CorpsRigide
{
public:
    Cone(float radius, float height, vec3 position, ofColor color):CorpsRigide(position, color)
    {
        this->radius = radius;
        this->height = height;
        rigidBody.setPosition(position);
        rigidBody.set(radius, height);
    };

    void draw() override
    {
        material.setDiffuseColor(color);
        material.setSpecularColor(ofColor(100, 100, 100));
        material.setShininess(50);
        material.begin();
        rigidBody.draw();
        material.end();
    }

    ofConePrimitive* getRigidBody() override { return &rigidBody; }

private:
    float radius;
    float height;
    ofConePrimitive rigidBody;
    
};
