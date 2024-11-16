#include "CorpsRigide.h"

#include "ofMaterial.h"
#include "ofxColorPicker.h"

CorpsRigide::CorpsRigide(vec3 position, vec3 extent, ofColor color)
{
    this->position = position;
    this->extent = extent;
    this->color = color;
    setMass(1);
    rigidBody.set(extent.x() * 2, extent.y() * 2, extent.z() * 2);
    calcJminusOne();
}

void CorpsRigide::update(double dt)
{
    //Euler
    acceleration = forces * inverseMass;
    velocity = velocity + acceleration * dt;
    this->position += velocity * dt;

    // on calcule le jminusone actuel pour prendre en compte l'orientation
    mat3 orientationMatrix = orientation.toMat3();
    mat3 JminusOnePrim = orientationMatrix * JminusOne * orientationMatrix.inverse();

    // calcul de l'acceleration a partir des forces accumulees dans tau
    angularAcceleration = tau * JminusOnePrim;

    // mise a jour de la velocite puis de l'orientation
    angularVelocity += angularAcceleration * dt;
    orientation = orientation + quaternion(0, angularVelocity) * 1/2 * orientation * dt;
    orientation.normalize(); // on s'assure que le quaternion represente une rotation
    
    rigidBody.setOrientation(orientation);
    rigidBody.setPosition(position);

    // reset force accumulation
    forces = vec3(0);
    tau = vec3(0);
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