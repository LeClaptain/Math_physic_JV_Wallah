#include "CorpsRigide.h"

#include "ofMaterial.h"
#include "ofxColorPicker.h"

CorpsRigide::CorpsRigide(vec3 position, vec3 extent, ofColor color)
{
    this->position = position;
    this->extent = extent;
    this->color = color;
    rigidBody.set(extent.x() * 2, extent.y() * 2, extent.z() * 2);

}

void CorpsRigide::update(double dt)
{
    //Euler
    acceleration = forces * inverseMass;
    velocity = velocity + acceleration * dt;
    this->position += velocity * dt;

    //TODO : accelleration ici stp
    angularVelocity = angularVelocity + angularAcceleration * dt;
    orientation = quaternion(1, 0, 0, 0) + quaternion(0, angularVelocity) * 1/2 * orientation *dt;
    orientation.normalize();
    rigidBody.rotate(orientation);
    rigidBody.setPosition(position);

}

void CorpsRigide::draw()
{
    //ofSetColor(color);
    material.setDiffuseColor(color);
    material.setSpecularColor(ofColor(100, 100, 100));
    material.setShininess(50);
    material.begin();
    rigidBody.draw();
    material.end();
}


void CorpsRigide::applyRotationFromQuaternion() {


    // Appliquer la rotation avec ofRotate
}